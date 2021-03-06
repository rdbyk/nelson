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
#include "strfindBuiltin.hpp"
#include "Error.hpp"
#include "OverloadFunction.hpp"
#include "StringFind.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::StringGateway::strfindBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    if (nLhs > 1) {
        Error(eval, ERROR_WRONG_NUMBERS_OUTPUT_ARGS);
    }
    if (!(argIn.size() == 2 || argIn.size() == 4)) {
        Error(eval, ERROR_WRONG_NUMBERS_INPUT_ARGS);
    }
    bool forceAsCell = false;
    if (argIn.size() == 4) {
        ArrayOf param3 = argIn[2];
        ArrayOf param4 = argIn[3];
        if (param3.isSingleString()) {
            std::wstring str = param3.getContentAsWideString();
            if (str != L"ForceCellOutput") {
                Error(eval, _W("'ForceCellOutput' expected as third input argument."));
            }
        } else {
            Error(eval, ERROR_WRONG_ARGUMENT_3_TYPE_STRING_EXPECTED);
        }
        if (param4.isScalar() && param4.isLogical()) {
            forceAsCell = param4.getContentAsLogicalScalar();
        } else {
            Error(eval, ERROR_WRONG_ARGUMENT_4_TYPE_LOGICAL_EXPECTED);
        }
    }
    ArrayOf A = argIn[0];
    ArrayOf B = argIn[1];
    // Call overload if it exists
    bool bSuccess = false;
    retval = OverloadFunction(eval, nLhs, argIn, bSuccess);
    if (!bSuccess) {
        if (A.isSingleString() || A.isCell() || A.isNumeric()) {
            if (B.isSingleString() || B.isNumeric()) {
                if (A.isSingleString()) {
                    if (B.isSingleString()) {
                        if ((B.isRowVector() && !B.isEmpty()) || B.isEmpty(true)) {
                            if (forceAsCell) {
                                Dimensions dimA(1, 1);
                                size_t nbElements = 1;
                                ArrayOf* elements = nullptr;
                                try {
                                    elements = new ArrayOf[nbElements];
                                } catch (std::bad_alloc& e) {
                                    e.what();
                                    Error(eval, ERROR_MEMORY_ALLOCATION);
                                }
                                for (size_t k = 0; k < nbElements; k++) {
                                    // ArrayOf *cellA = (ArrayOf*)(A.getDataPointer());
                                    elements[k] = StringFind(
                                        A.getContentAsWideString(), B.getContentAsWideString());
                                }
                                retval.push_back(ArrayOf(NLS_CELL_ARRAY, dimA, elements));
                            } else {
                                retval.push_back(StringFind(
                                    A.getContentAsWideString(), B.getContentAsWideString()));
                            }
                        } else {
                            Error(eval, _W("Second argument a single string expected."));
                        }
                    } else {
                        retval.push_back(ArrayOf::emptyConstructor());
                    }
                } else if (A.isCell()) {
                    Dimensions dimA = A.getDimensions();
                    size_t nbElements = dimA.getElementCount();
                    ArrayOf* elements = nullptr;
                    try {
                        elements = new ArrayOf[nbElements];
                    } catch (std::bad_alloc& e) {
                        e.what();
                        Error(eval, ERROR_MEMORY_ALLOCATION);
                    }
                    for (size_t k = 0; k < nbElements; k++) {
                        ArrayOf* cellA = (ArrayOf*)(A.getDataPointer());
                        if (cellA[k].isSingleString()) {
                            if (B.isSingleString()) {
                                if ((B.isRowVector() && !B.isEmpty()) || B.isEmpty(true)) {
                                    std::wstring valB = B.getContentAsWideString();
                                    elements[k]
                                        = StringFind(cellA[k].getContentAsWideString(), valB);
                                } else {
                                    Error(eval, _W("Second argument a single string expected."));
                                }
                            } else {
                                elements[k] = ArrayOf::emptyConstructor();
                            }
                        } else {
                            Error(eval,
                                _W("First argument must be a cell of strings (or a string) and "
                                   "second argument a string."));
                        }
                    }
                    retval.push_back(ArrayOf(NLS_CELL_ARRAY, dimA, elements));
                } else if (A.isNumeric()) {
                    if ((A.isRowVector() && !A.isEmpty()) || A.isScalar() || A.isEmpty(true)) {
                        retval.push_back(ArrayOf::emptyConstructor());
                    } else {
                        Error(eval, _W("Input strings must have one row."));
                    }
                } else {
                    Error(eval,
                        _W("First argument must be a cell of strings (or a string) and second "
                           "argument a string."));
                }
            } else {
                Error(eval, _W("Second argument a single string expected."));
            }
        } else {
            Error(eval,
                _W("First argument must be a cell of strings (or a string) and second argument a "
                   "string."));
        }
    }
    return retval;
}
//=============================================================================
