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
#define H5_BUILT_AS_DYNAMIC_LIB
#include <hdf5.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include "HDF5_helpers.hpp"
#include "h5WriteAttribute.hpp"
#include "Exception.hpp"
#include "Error.hpp"
#include "characters_encoding.hpp"
#include "h5WriteHelpers.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
void
h5WriteAttribute(const std::wstring& filename, const std::wstring& location,
    const std::wstring& attributeName, ArrayOf& attributeValue, const std::wstring& textEncoding)
{
    if (filename.empty()) {
        Error(_W("Valid filename expected."));
    }
    if (location.empty()) {
        Error(_W("Valid location expected."));
    }
    if (attributeName.empty()) {
        Error(_W("Valid attribute name expected."));
    }
    if (!(textEncoding == L"system" || textEncoding == L"UTF-8")) {
        Error(_W("Valid text encoding expected."));
    }
    hid_t fid = H5I_INVALID_HID;
    boost::filesystem::path hdf5_filename(filename);
    bool fileExistPreviously = false;
    try {
        fileExistPreviously = boost::filesystem::exists(hdf5_filename)
            && !boost::filesystem::is_directory(hdf5_filename);
    } catch (const boost::filesystem::filesystem_error& e) {
        if (e.code() == boost::system::errc::permission_denied) {
            Error(_W("Permission denied."));
        }
        fileExistPreviously = false;
    }
    if (!fileExistPreviously) {
        Error(_W("file does not exist."));
    } else {
        if (!H5Fis_hdf5(wstring_to_utf8(hdf5_filename.wstring()).c_str()))
            Error(_W("HDF5 format file expected."));
        else {
            fid = H5Fopen(
                wstring_to_utf8(hdf5_filename.wstring()).c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
        }
    }
    if (fid == H5I_INVALID_HID) {
        Error(_W("Open file failed."));
    }
    if (location != L"/" && !H5Lexists(fid, wstring_to_utf8(location).c_str(), H5P_DEFAULT)) {
        H5Fclose(fid);
        Error(_W("Specified HDF5 object location does not exist."));
    }
    hid_t obj_id = H5Oopen(fid, wstring_to_utf8(location).c_str(), H5P_DEFAULT);
    if (obj_id < 0) {
        H5Fclose(fid);
        Error(_W("Specified HDF5 object location could not be opened."));
    }

    htri_t exists = H5Aexists(obj_id, wstring_to_utf8(attributeName).c_str());
    if (exists > 0) {
        if (H5Adelete(obj_id, wstring_to_utf8(attributeName).c_str()) < 0) {
            H5Oclose(obj_id);
            H5Fclose(fid);
            Error(_W("Could not delete existing attribute."));
        }
    } else if (exists < 0) {
        H5Oclose(obj_id);
        H5Fclose(fid);
        Error(_W("Could not check if attribute exists."));
    }

    if (attributeValue.isSparse()) {
        attributeValue.makeDense();
    }
    hid_t type_id = H5I_INVALID_HID;
    hid_t dspace_id = H5I_INVALID_HID;
    std::wstring error;
    void* buffer = h5WriteNelsonToHdf5(attributeValue, type_id, dspace_id, error);
    if (!error.empty()) {
        H5Aclose(exists);
        H5Oclose(obj_id);
        H5Fclose(fid);
        Error(error);
    }
    hid_t att_id = H5I_INVALID_HID;
    if (H5Aexists(obj_id, wstring_to_utf8(attributeName).c_str()))
        att_id = H5Aopen(obj_id, wstring_to_utf8(attributeName).c_str(), H5P_DEFAULT);
    else {
        att_id = H5Acreate(obj_id, wstring_to_utf8(attributeName).c_str(), type_id, dspace_id,
            H5P_DEFAULT, H5P_DEFAULT);
    }
    herr_t status = H5I_INVALID_HID;
    if (att_id > 0) {
        status = H5Awrite(att_id, type_id, buffer);
    }
    H5Sclose(dspace_id);
    H5Aclose(att_id);
    H5Oclose(obj_id);
    H5Fclose(fid);
    if (status < 0) {
        Error(_W("Cannot write attribute."));
    }
}
//=============================================================================
} // namespace Nelson
//=============================================================================
