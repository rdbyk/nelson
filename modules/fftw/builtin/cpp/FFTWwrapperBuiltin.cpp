//=============================================================================
// Copyright (c) 2016-2019 Allan CORNET (Nelson)
//=============================================================================
// LICENCE_BLOCK_BEGIN
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// LICENCE_BLOCK_END
//=============================================================================
#include "FFTWwrapperBuiltin.hpp"
#include "FFTWDynamicLibrary.hpp"
#include "Error.hpp"
#include "ModulePath.hpp"
#include "GetNelsonPath.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::FftwGateway::FFTWwrapperBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 1) {
        Error(ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    switch (argIn.size()) {
    case 1: {
        std::wstring param1 = argIn[0].getContentAsWideString();
        if (param1 == L"load") {
            std::wstring binaryPath
                = ModulePath(GetNelsonPath(), L"fftw", Nelson::MODULEPATH_OPTION::GET_BINARY_PATH);
            retval.push_back(ArrayOf::logicalConstructor(loadFFTWLibrary(binaryPath)));
        } else if (param1 == L"free") {
            retval.push_back(ArrayOf::logicalConstructor(freeFFTWLibrary()));
        } else {
            Error(_W("Wrong value for #1: 'load' or 'free' expected."));
        }
    } break;
    case 3: {
        std::wstring param1 = argIn[0].getContentAsWideString();
        if (param1 == L"load") {
          std::wstring fftwName = argIn[0].getContentAsWideString();
          std::wstring fftwfName = argIn[1].getContentAsWideString();
          retval.push_back(ArrayOf::logicalConstructor(loadFFTWLibrary(fftwName, fftwfName)));
        } else {
            Error(_W("Wrong value for #1: 'load' expected."));
        }
    } break;
    default: {
        Error(ERROR_WRONG_NUMBERS_INPUT_ARGS);
    } break;
    }
    return retval;
}
//=============================================================================