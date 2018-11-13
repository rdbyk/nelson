//=============================================================================
// Copyright (c) 2016-2018 Allan CORNET (Nelson)
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
#include "stringBuiltin.hpp"
#include "Error.hpp"
#include "OverloadFunction.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::StringGateway::stringBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 1) {
        Error(ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (argIn.size() > 1) {
        Error(ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (argIn.empty()) {
        retval.push_back(ArrayOf::stringArrayConstructor(std::string("")));
    } else {
        bool bSuccess = false;
        if (eval->mustOverloadBasicTypes()) {
            retval = OverloadFunction(eval, nLhs, argIn, "string", bSuccess);
        }
        if (!bSuccess) {
            bool needToOverload = false;
            ArrayOf res = ArrayOf::toStringArray(argIn[0], needToOverload);
            if (needToOverload) {
                retval = OverloadFunction(eval, nLhs, argIn, "string");
            } else {
                retval.push_back(res);
            }
        }
    }
    return retval;
}
//=============================================================================