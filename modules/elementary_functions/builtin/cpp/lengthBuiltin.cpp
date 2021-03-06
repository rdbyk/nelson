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
#include "lengthBuiltin.hpp"
#include "ClassName.hpp"
#include "Error.hpp"
#include "OverloadFunction.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::ElementaryFunctionsGateway::lengthBuiltin(
    Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (argIn.size() != 1) {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    if (nLhs > 1) {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    // Call overload if it exists
    bool bSuccess = false;
    retval = OverloadFunction(eval, nLhs, argIn, bSuccess);
    if (!bSuccess) {
        ArrayOf param1 = argIn[0];
        if (param1.isClassStruct()) {
            Error(eval,
                _("Undefined function 'length' for input arguments of type") + " '"
                    + ClassName(param1) + "'.");
        }
        double len = 0;
        Dimensions sze(param1.getDimensions());
        for (indexType i = 0; i < sze.getLength(); i++) {
            if ((double)sze[i] == 0) {
                len = 0;
                break;
            }
            if (i == 0) {
                len = (double)sze[i];
            } else {
                if ((double)sze[i] > len) {
                    len = (double)sze[i];
                }
            }
        }
        retval.push_back(ArrayOf::doubleConstructor(len));
    }
    return retval;
}
//=============================================================================
