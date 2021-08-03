/**
	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#include <FileWatcherWin32.h>
#include "characters_encoding.hpp"

#if FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_WIN32

#define _WIN32_WINNT 0x0550
#include <windows.h>

#if defined(_MSC_VER)
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ole32.lib")

// disable secure warnings
#pragma warning (disable: 4996)
#endif

namespace FW {
	/// Internal watch data
	struct WatchStruct
	{
		OVERLAPPED mOverlapped;
		HANDLE mDirHandle;
		BYTE mBuffer[32 * 1024];
		LPARAM lParam;
		DWORD mNotifyFilter;
		bool mStopNow;
		FileWatcherImpl* mFileWatcher;
		FileWatchListener* mFileWatchListener;
    	wchar_t* mDirName;
		WatchID mWatchid;
		bool mIsRecursive;
	};

#pragma region Internal Functions

	// forward decl
	bool
	RefreshWatch(WatchStruct* pWatch, bool _clear = false);

	/// Unpacks events and passes them to a user defined callback.
	void CALLBACK 
	WatchCallback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
	{
		PFILE_NOTIFY_INFORMATION pNotify;
		auto* pWatch = (WatchStruct*) lpOverlapped;
		size_t offset = 0;

		if(dwNumberOfBytesTransfered == 0) {
			return;
}

		if (dwErrorCode == ERROR_SUCCESS)
		{
			do
			{
				pNotify = (PFILE_NOTIFY_INFORMATION) &pWatch->mBuffer[offset];
				offset += pNotify->NextEntryOffset;
				pWatch->mFileWatcher->handleAction(pWatch, pNotify->FileName, pNotify->Action);

			} while (pNotify->NextEntryOffset != 0);
		}
		if (!pWatch->mStopNow) {
			RefreshWatch(pWatch);
		}
	}

	/// Refreshes the directory monitoring.
	bool 
	RefreshWatch(WatchStruct* pWatch, bool _clear)
	{
    return ReadDirectoryChangesW(pWatch->mDirHandle, pWatch->mBuffer, sizeof(pWatch->mBuffer),
               static_cast<BOOL>(pWatch->mIsRecursive), pWatch->mNotifyFilter, nullptr,
               &pWatch->mOverlapped, _clear ? nullptr : WatchCallback)
        != 0;
		}

	/// Stops monitoring a directory.
	void
	DestroyWatch(WatchStruct* pWatch)
	{
		if (pWatch != nullptr) {
			pWatch->mStopNow = TRUE;
			CancelIo(pWatch->mDirHandle);
			RefreshWatch(pWatch, true);
			if (!HasOverlappedIoCompleted(&pWatch->mOverlapped)) {
				SleepEx(2, TRUE);
			}
			CloseHandle(pWatch->mOverlapped.hEvent);
			CloseHandle(pWatch->mDirHandle);
		    if (pWatch->mDirName != nullptr) {
            delete [] pWatch->mDirName;
            pWatch->mDirName = nullptr;
        	}	
			HeapFree(GetProcessHeap(), 0, pWatch);
		}
	}

	/// Starts monitoring a directory.
	WatchStruct*
    CreateWatch(LPCTSTR szDirectory, bool recursive, DWORD mNotifyFilter)
	{
		WatchStruct* pWatch;
		size_t ptrsize = sizeof(*pWatch);
		pWatch = static_cast<WatchStruct*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptrsize));
		pWatch->mDirHandle = CreateFile(szDirectory, FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, 
			OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

		if (pWatch->mDirHandle != INVALID_HANDLE_VALUE) {
			pWatch->mOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
			pWatch->mNotifyFilter = mNotifyFilter;
			pWatch->mIsRecursive = recursive;
			if (RefreshWatch(pWatch)) {
				return pWatch;
			}
			
			
				CloseHandle(pWatch->mOverlapped.hEvent);
				CloseHandle(pWatch->mDirHandle);
			
		}

		HeapFree(GetProcessHeap(), 0, pWatch);
		return nullptr;
	}

#pragma endregion

	//--------
	FileWatcherWin32::FileWatcherWin32()  {}

	//--------
	FileWatcherWin32::~FileWatcherWin32()
	{
    	auto iter = mWatches.begin();
    	auto end = mWatches.end();
		for(; iter != end; ++iter)
		{
			DestroyWatch(iter->second);
		}
		mWatches.clear();
	}

	//--------
	WatchID
	FileWatcherWin32::addWatch(const String& directory, FileWatchListener* watcher, bool recursive)
	{
		WatchID watchid = ++mLastWatchID;
		WatchStruct* watch = CreateWatch(directory.c_str(), recursive,
			FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_FILE_NAME);

		if(watch == nullptr) {
			throw FileNotFoundException(directory);
		}
		watch->mWatchid = watchid;
		watch->mFileWatcher = this;
		watch->mFileWatchListener = watcher;
	    watch->mDirName = new wchar_t[directory.length() + 1];
    	wcscpy(watch->mDirName, directory.c_str());
		mWatches.insert(std::make_pair(watchid, watch));
		return watchid;
	}

	//--------
	void
	FileWatcherWin32::removeWatch(const String& directory)
	{
	    auto iter = mWatches.begin();
    	auto end = mWatches.end();
		for(; iter != end; ++iter) {
			if(directory == iter->second->mDirName) {
				removeWatch(iter->first);
				return;
			}
		}
	}

	//--------
	void 
	FileWatcherWin32::removeWatch(WatchID watchid)
	{
	    auto iter = mWatches.find(watchid);
		if(iter == mWatches.end()) {
			return;
		}
		WatchStruct* watch = iter->second;
		mWatches.erase(iter);
		DestroyWatch(watch);
	}

	//--------
	void 
	FileWatcherWin32::update()
	{
		MsgWaitForMultipleObjectsEx(0, nullptr, 0, QS_ALLINPUT, MWMO_ALERTABLE);
	}

	//--------
	void 
	FileWatcherWin32::handleAction(WatchStruct* watch, const String& filename, unsigned long action)
	{
		Action fwAction;
		switch (action) {
		case FILE_ACTION_RENAMED_NEW_NAME:
		case FILE_ACTION_ADDED:
			fwAction = Actions::Add;
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
		case FILE_ACTION_REMOVED:
			fwAction = Actions::Delete;
			break;
		case FILE_ACTION_MODIFIED:
			fwAction = Actions::Modified;
			break;
		};
		if (watch != nullptr) {
			if (watch->mDirName != nullptr) {
				watch->mFileWatchListener->handleFileAction(
					watch->mWatchid, watch->mDirName, filename, fwAction);
			}
		}
	}

};//namespace FW

#endif//_WIN32
