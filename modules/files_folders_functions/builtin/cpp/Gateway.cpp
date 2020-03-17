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
#include "NelsonGateway.hpp"
#include "cdBuiltin.hpp"
#include "copyfileBuiltin.hpp"
#include "diff_fileBuiltin.hpp"
#include "dirBuiltin.hpp"
#include "filepartsBuiltin.hpp"
#include "filesepBuiltin.hpp"
#include "isdirBuiltin.hpp"
#include "isfileBuiltin.hpp"
#include "mkdirBuiltin.hpp"
#include "pathsepBuiltin.hpp"
#include "pwdBuiltin.hpp"
#include "relativepathBuiltin.hpp"
#include "rmdirBuiltin.hpp"
#include "rmfileBuiltin.hpp"
#include "tempdirBuiltin.hpp"
#include "userdirBuiltin.hpp"
#include "fullpathBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
const std::wstring gatewayName = L"files_folders_functions";
//=============================================================================
static const nlsGateway gateway[] = {
    { "pwd", (void*)Nelson::FilesFoldersGateway::pwdBuiltin, 1, 0, CPP_BUILTIN_WITH_EVALUATOR },
    { "cd", (void*)Nelson::FilesFoldersGateway::cdBuiltin, 1, 1, CPP_BUILTIN_WITH_EVALUATOR },
    { "dir", (void*)Nelson::FilesFoldersGateway::dirBuiltin, 1, 1, CPP_BUILTIN_WITH_EVALUATOR },
    { "isdir", (void*)Nelson::FilesFoldersGateway::isdirBuiltin, 1, 1, CPP_BUILTIN },
    { "isfolder", (void*)Nelson::FilesFoldersGateway::isdirBuiltin, 1, 1, CPP_BUILTIN },
    { "isfile", (void*)Nelson::FilesFoldersGateway::isfileBuiltin, 1, 1, CPP_BUILTIN },
    { "fileparts", (void*)Nelson::FilesFoldersGateway::filepartsBuiltin, 3, 2, CPP_BUILTIN },
    { "mkdir", (void*)Nelson::FilesFoldersGateway::mkdirBuiltin, 2, 2, CPP_BUILTIN },
    { "relativepath", (void*)Nelson::FilesFoldersGateway::relativepathBuiltin, 1, 2, CPP_BUILTIN },
    { "rmdir", (void*)Nelson::FilesFoldersGateway::rmdirBuiltin, 2, 2, CPP_BUILTIN },
    { "copyfile", (void*)Nelson::FilesFoldersGateway::copyfileBuiltin, 2, 3, CPP_BUILTIN },
    { "diff_file", (void*)Nelson::FilesFoldersGateway::diff_fileBuiltin, 1, -2, CPP_BUILTIN },
    { "rmfile", (void*)Nelson::FilesFoldersGateway::rmfileBuiltin, 2, 1, CPP_BUILTIN },
    { "pathsep", (void*)Nelson::FilesFoldersGateway::pathsepBuiltin, 1, 0, CPP_BUILTIN },
    { "filesep", (void*)Nelson::FilesFoldersGateway::filesepBuiltin, 1, 0, CPP_BUILTIN },
    { "fullpath", (void*)Nelson::FilesFoldersGateway::fullpathBuiltin, 1, 1, CPP_BUILTIN },
    { "tempdir", (void*)Nelson::FilesFoldersGateway::tempdirBuiltin, 1, 0, CPP_BUILTIN },
    { "userdir", (void*)Nelson::FilesFoldersGateway::userdirBuiltin, 1, 0, CPP_BUILTIN },
};
//=============================================================================
NLSGATEWAYFUNC(gateway)
//=============================================================================
NLSGATEWAYINFO(gateway)
//=============================================================================
NLSGATEWAYREMOVE(gateway)
//=============================================================================
NLSGATEWAYNAME()
//=============================================================================
