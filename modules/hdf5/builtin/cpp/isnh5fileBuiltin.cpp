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
#include "isnh5fileBuiltin.hpp"
#include "isNh5File.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
// isnh5file(filename)
//=============================================================================
ArrayOfVector
Nelson::Hdf5Gateway::isnh5fileBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 3) {
        Error(ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    indexType nbArgIn = argIn.size();
    if (nbArgIn != 1) {
        Error(ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    wstringVector filenames = argIn[0].getContentAsWideStringVector(true);
    ArrayOf isNh5;
    ArrayOf nh5Versions;
    ArrayOf nh5Headers;
    isNh5File(filenames, isNh5, nh5Versions, nh5Headers);
    retval.push_back(isNh5);
    if (nLhs > 1) {
        retval.push_back(nh5Versions);
    }
    if (nLhs > 2) {
        retval.push_back(nh5Headers);
    }
    return retval;
}
//=============================================================================
