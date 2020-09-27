//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program. If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <mz_compat.h>
#include "Unzip.hpp"
#include "UnzipHelpers.hpp"
#include "ZipHelpers.hpp"
#include "characters_encoding.hpp"
#include "Error.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
void
UnZip(const std::wstring& zipFilename, const std::wstring& rootpath, wstringVector& filenames)
{
    if (!isExistingDirectory(rootpath)) {
        try {
#ifdef _MSC_VER
            boost::filesystem::path p = rootpath;
#else
            boost::filesystem::path p = wstring_to_utf8(rootpath);
#endif
            boost::filesystem::create_directories(p);
        } catch (const boost::filesystem::filesystem_error&) {
            Error(_W("Cannot create directory."));
        }
    }
    std::wstring fullRootPath = getRootPath(rootpath);

    unzFile* zipfile = static_cast<unzFile*>(unzOpen64(wstring_to_utf8(zipFilename).c_str()));
    if (zipfile == nullptr) {
        Error(_W("Cannot read file:") + L" " + zipFilename);
    }

    unz_global_info64 global_info;
    if (unzGetGlobalInfo64(zipfile, &global_info) != UNZ_OK) {
        Error(_W("Cannot read file global info."));
    }
#define MAX_FILENAME 8192
    for (size_t i = 0; i < global_info.number_entry; ++i) {
        unz_file_info64 file_info;
        char filename[MAX_FILENAME];
        if (unzGetCurrentFileInfo64(
                zipfile, &file_info, filename, MAX_FILENAME, nullptr, 0, nullptr, 0)
            != UNZ_OK) {
            unzClose(zipfile);
            Error(_W("Cannot read file info."));
        }
        const size_t filename_length = strlen(filename);
        if (filename[filename_length - 1] == '/') {
            std::wstring completePath = fullRootPath + L"/" + utf8_to_wstring(filename);
            if (!isExistingDirectory(completePath)) {
                try {
#ifdef _MSC_VER
                    boost::filesystem::create_directories(completePath);
#else
                    boost::filesystem::create_directories(wstring_to_utf8(completePath));
#endif
                } catch (const boost::filesystem::filesystem_error& e) {
                    boost::system::error_code error_code = e.code();
                }
            }
            filenames.push_back(completePath);
        } else {
            if (unzOpenCurrentFile(zipfile) != UNZ_OK) {
                unzClose(zipfile);
                Error(_W("Cannot open file."));
            }
            std::wstring completePath = fullRootPath + L"/" + utf8_to_wstring(filename);
#ifdef _MSC_VER
            FILE* out = _wfopen(completePath.c_str(), L"wb");
#else
            FILE* out = fopen(wstring_to_utf8(completePath).c_str(), "wb");
#endif
            if (out == nullptr) {
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                Error(_W("Cannot open destination file."));
            }
            filenames.push_back(completePath);

            int error = UNZ_OK;
            char read_buffer[MAX_FILENAME];
            do {
                error = unzReadCurrentFile(zipfile, read_buffer, MAX_FILENAME);
                if (error < 0) {
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    if (out != nullptr) {
                        fclose(out);
                        out = nullptr;
                    }
                    Error(_W("Cannot read data."));
                }
                if (error > 0) {
                    fwrite(read_buffer, error, 1, out);
                }
            } while (error > 0);
            unzCloseCurrentFile(zipfile);
            if (out != nullptr) {
                fclose(out);
                out = nullptr;
            }
            changeFileDate(completePath, file_info.tmu_date, file_info.dosDate);
            changeFileOrFolderAttributes(completePath, file_info.external_fa);
        }
        if ((i + 1) < global_info.number_entry) {
            if (unzGoToNextFile(zipfile) != UNZ_OK) {
                unzClose(zipfile);
                Error(_W("Cannot read next file."));
            }
        }
    }
    unzClose(zipfile);
}
//=============================================================================
} // namespace Nelson
//=============================================================================
