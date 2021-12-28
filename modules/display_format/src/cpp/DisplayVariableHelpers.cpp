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
#include <fmt/printf.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include <cstring>
#include <algorithm>
#include <limits>
#include <boost/algorithm/string.hpp>
#include "DisplayVariableHelpers.hpp"
#include "NelsonConfiguration.hpp"
#include "IEEEFP.hpp"
#include "characters_encoding.hpp"
#include "DisplayIntegerHelpers.hpp"
#include "FormatShort.hpp"
#include "FormatShortE.hpp"
#include "FormatShortG.hpp"
#include "FormatShortEng.hpp"
#include "FormatLongE.hpp"
#include "FormatLongG.hpp"
#include "FormatLongEng.hpp"
#include "FormatBank.hpp"
#include "FormatPlus.hpp"
#include "FormatHex.hpp"
#include "FormatRational.hpp"
#include "FormatHelpers.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
template <class T>
void
getMinMax(T* val, indexType nbElements, T* min, T* max)
{
    T minValue = val[0];
    T maxValue = val[0];
    T shared_max = maxValue;
    T shared_min = minValue;

#pragma omp parallel
    {
#pragma omp for nowait
        for (ompIndexType idx = 0; idx < (ompIndexType)nbElements; ++idx) {
            maxValue = std::max(val[idx], maxValue);
            minValue = std::max(val[idx], minValue);
        }
#pragma omp critical
        {
            shared_max = std::max(shared_max, maxValue);
            shared_min = std::max(shared_min, minValue);
        }
    }
    *min = shared_min;
    *max = shared_max;
}
//=============================================================================
template <class T>
T
getMax(T* val, indexType nbElements)
{
    T maxValue = val[0];
    T shared_max = maxValue;
#pragma omp parallel
    {
#pragma omp for nowait
        for (ompIndexType idx = 0; idx < (ompIndexType)nbElements; ++idx) {
            maxValue = std::max(val[idx], maxValue);
        }
#pragma omp critical
        {
            shared_max = std::max(shared_max, maxValue);
        }
    }
    return shared_max;
}
//=============================================================================
template <class T>
T
getMin(T* val, indexType nbElements)
{
    T minValue = val[0];
    T shared_min = minValue;
#pragma omp parallel
    {
#pragma omp for nowait
        for (ompIndexType idx = 0; idx < (ompIndexType)nbElements; ++idx) {
            minValue = std::min(val[idx], minValue);
        }
#pragma omp critical
        {
            shared_min = std::max(shared_min, minValue);
        }
    }
    return shared_min;
}
//=============================================================================
std::wstring
completeWithBlanksAtBeginning(const std::wstring& msg, NumericFormatDisplay currentNumericFormat)
{
    size_t width = 10;
    switch (currentNumericFormat) {
    case NLS_NUMERIC_FORMAT_SHORT: {
        width = 13;
    } break;
    case NLS_NUMERIC_FORMAT_LONG: {
        width = 0;
    } break;
    default: {
    } break;
    }
    return completeWithBlanksAtBeginning(msg, width);
}
//=============================================================================
std::wstring
completeWithBlanksAtBeginning(const std::wstring& msg, size_t width)
{
    size_t len = msg.length();
    std::wstring blanks;
    if (int(width) - int(len) > 0) {
        blanks.append(width - len, L' ');
        return blanks + msg;
    }
    return msg;
}
//=============================================================================
static std::wstring
getClassAsWideString(const ArrayOf& A)
{
    std::wstring typeAsText;
    switch (A.getDataClass()) {
    case NLS_GO_HANDLE:
        typeAsText = L"graphic_object";
        break;
    case NLS_HANDLE:
        typeAsText = L"handle";
        break;
    case NLS_UINT8:
        typeAsText = L"uint8";
        break;
    case NLS_INT8:
        typeAsText = L"int8";
        break;
    case NLS_UINT16:
        typeAsText = L"uint16";
        break;
    case NLS_INT16:
        typeAsText = L"int16";
        break;
    case NLS_UINT32:
        typeAsText = L"uint32";
        break;
    case NLS_INT32:
        typeAsText = L"int32";
        break;
    case NLS_UINT64:
        typeAsText = L"uint64";
        break;
    case NLS_INT64:
        typeAsText = L"int64";
        break;
    case NLS_SINGLE:
        typeAsText = L"single";
        break;
    case NLS_DOUBLE: {
        if (A.isSparse()) {
            typeAsText = L"sparse double";
        } else {
            typeAsText = L"double";
        }
    } break;
    case NLS_LOGICAL: {
        if (A.isSparse()) {
            typeAsText = L"sparse logical";
        } else {
            typeAsText = L"logical";
        }
    } break;
    case NLS_CHAR:
        typeAsText = L"char";
        break;
    case NLS_SCOMPLEX:
        typeAsText = L"single";
        break;
    case NLS_DCOMPLEX: {
        if (A.isSparse()) {
            typeAsText = L"sparse double";
        } else {
            typeAsText = L"double";
        }
    } break;
    case NLS_CELL_ARRAY:
        typeAsText = L"cell";
        break;
    case NLS_STRUCT_ARRAY: {
        if (A.isClassStruct()) {
            typeAsText = utf8_to_wstring(A.getStructType());
        } else {
            typeAsText = utf8_to_wstring(NLS_STRUCT_ARRAY_STR);
        }
    } break;
    case NLS_STRING_ARRAY:
        typeAsText = L"string";
        break;
    default: {
    } break;
    }
    return typeAsText;
}
//=============================================================================
static std::wstring
buildHeader(const ArrayOf& A)
{
    std::wstring msg;
    std::wstring typeAsText = getClassAsWideString(A);
    if (A.isScalar() && !(A.isCell() || A.isStruct())) {
        msg = L"  " + typeAsText + L"\n";
    } else {
        std::wstring dimensions = A.getDimensions().toWideString();
        std::wstring dimensionsForHuman = L"";
        switch (A.getDataClass()) {
        case NLS_STRUCT_ARRAY: {
            stringVector fieldnames = A.getFieldNames();
            bool haveFields = !fieldnames.empty();
            bool isEmpty = A.isEmpty();
            bool isScalar = A.isScalar();
            std::wstring withPart;

            if (A.isClassStruct()) {
                if (!haveFields) {
                    withPart = L"with no properties.";
                } else {
                    withPart = L"with properties:";
                }
            } else {
                if (!haveFields) {
                    withPart = L"with no fields.";
                } else {
                    withPart = L"with fields:";
                }
            }
            dimensionsForHuman = isEmpty || !isScalar ? L"array" : L"";
            if (isEmpty) {
                msg = fmt::sprintf(L"  %s %s %s %s %s", dimensions, L"empty", typeAsText,
                    dimensionsForHuman, withPart);
            } else if (isScalar) {
                msg = fmt::sprintf(L"  %s %s", typeAsText, withPart);
            } else {
                msg = fmt::sprintf(
                    L"  %s %s %s %s", dimensions, typeAsText, dimensionsForHuman, withPart);
            }
            msg.append(L"\n");
            return msg;
        } break;
        case NLS_LOGICAL:
        case NLS_CELL_ARRAY:
        case NLS_STRING_ARRAY:
        case NLS_CHAR: {
            dimensionsForHuman = _W("array");
        } break;
        default: {
            if (A.getDimensions().getLength() > 2) {
                dimensionsForHuman = _W("array");
            } else if (A.isRowVector()) {
                dimensionsForHuman = _W("row vector");
            } else if (A.isColumnVector()) {
                dimensionsForHuman = _W("column vector");
            } else {
                dimensionsForHuman = _W("matrix");
            }
        } break;
        }
        if (!A.isEmpty()) {
            msg = fmt::sprintf(L"  %s %s %s", dimensions, typeAsText, dimensionsForHuman);
        } else {
            std::wstring empty = _W("empty");
            msg = fmt::sprintf(L"  %s %s %s %s", dimensions, empty, typeAsText, dimensionsForHuman);
        }
        msg.append(L"\n");
    }
    return msg;
}
//=============================================================================
void
DisplayVariableHeader(Interface* io, const ArrayOf& A, const std::wstring& name)
{
    if (!name.empty()) {
        bool isNdArray = (A.getDimensions().getLength() > 2);
        if (NelsonConfiguration::getInstance()->getLineSpacingDisplay()
            == NLS_LINE_SPACING_COMPACT) {
            if (!isNdArray) {
                io->outputMessage(name + L" =\n");
            }
        } else {
            io->outputMessage(L"\n");
            if (!isNdArray) {
                io->outputMessage(name + L" =\n\n");
            }
        }
        switch (A.getDataClass()) {
        case NLS_CHAR: {
            bool withType = A.isEmpty() || !A.isRowVector();
            if (withType) {
                std::wstring msg = buildHeader(A);
                io->outputMessage(msg);
            }
        } break;
        case NLS_DOUBLE:
        case NLS_DCOMPLEX: {
            if (A.isEmpty()) {
                std::wstring msg = buildHeader(A);
                io->outputMessage(msg);
            }
        } break;
        case NLS_STRING_ARRAY: {
            if (!A.isScalar()) {
                std::wstring msg = buildHeader(A);
                io->outputMessage(msg);
            }
        } break;

        case NLS_GO_HANDLE:
        case NLS_HANDLE:
        case NLS_CELL_ARRAY:
        case NLS_STRUCT_ARRAY:
        case NLS_LOGICAL:
        case NLS_UINT8:
        case NLS_INT8:
        case NLS_UINT16:
        case NLS_INT16:
        case NLS_UINT32:
        case NLS_INT32:
        case NLS_UINT64:
        case NLS_INT64:
        case NLS_SINGLE:
        case NLS_SCOMPLEX:
        default: {
            std::wstring msg = buildHeader(A);
            io->outputMessage(msg);
        } break;
        }
    }
}
//=============================================================================
void
DisplayVariableFooter(Interface* io, const ArrayOf& A, const std::wstring& name)
{
    if (NelsonConfiguration::getInstance()->getLineSpacingDisplay() == NLS_LINE_SPACING_LOOSE) {
        io->outputMessage(L"\n");
    }
}
//=============================================================================
std::wstring
summarizeStringArray(const ArrayOf& A, size_t beginingLineLength, size_t termWidth)
{
    std::wstring str;
    if (A.isEmpty()) {
        if (A.isCharacterArray()) {
            str = L"\"\"";
        } else {
            str = L"<missing>";
        }
    } else {
        if (A.getDataClass() == NLS_DOUBLE) {
            str = L"<missing>";
        } else if (A.getDataClass() == NLS_CHAR) {
            Dimensions dims = A.getDimensions();
            if (dims.isRowVector()) {
                if (dims.getColumns() < static_cast<indexType>(termWidth - 3)) {
                    std::wstring str = A.getContentAsWideString();
                    str = L"\"" + str + L"\"";
                    return str;
                }
            }
            str = lightDescription(A, L"[", L"]");
        }
    }
    return str;
}
//=============================================================================
/**
 * Print this object when it is an element of a cell array.  This is
 * generally a shorthand summary of the description of the object.
 */
std::wstring
summarizeCellEntry(const ArrayOf& A, size_t beginingLineLength, size_t termWidth,
    NumericFormatDisplay currentNumericFormat)
{
    std::wstring msg;
    if (A.isEmpty()) {
        if (A.getDataClass() == NLS_CHAR) {
            msg = L"''";
        } else {
            msg = L"[]";
        }
        return msg;
    }
    switch (A.getDataClass()) {
    case NLS_CELL_ARRAY: {
        if (A.isScalar()) {
            ArrayOf* elements = (ArrayOf*)A.getDataPointer();
            msg = L"{"
                + summarizeCellEntry(
                    elements[0], beginingLineLength + 1, termWidth, currentNumericFormat)
                + L"}";
        } else {
            msg = lightDescription(A, L"{", L"}");
        }
    } break;
    case NLS_STRING_ARRAY: {
        if (A.isScalar()) {
            ArrayOf* elements = (ArrayOf*)A.getDataPointer();
            if (elements[0].isCharacterArray()) {
                if (elements[0].getColumns() < termWidth - beginingLineLength - 3) {
                    msg = L"\"" + elements[0].getContentAsWideString() + L"\"";
                } else {
                    msg = lightDescription(A, L"[", L"]");
                }
            } else {
                msg = L"<missing>";
            }
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_STRUCT_ARRAY: {
        msg = lightDescription(A, L"[", L"]");
    } break;
    case NLS_CHAR: {
        if (A.isRowVector()) {
            if (A.getColumns() < termWidth - beginingLineLength - 3) {
                msg = L"\'" + A.getContentAsWideString() + L"\'";
            } else {
                msg = lightDescription(A, L"[", L"]");
            }
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_GO_HANDLE: {
        msg = lightDescription(A, L"[", L"]");
    } break;
    case NLS_HANDLE: {
        msg = lightDescription(A, L"[", L"]");
    } break;
    case NLS_LOGICAL: {
        if (A.isScalar()) {
            if (A.isSparse()) {
                msg = lightDescription(A, L"[", L"]");
            } else {
                logical val = A.getContentAsLogicalScalar();
                if (val) {
                    msg = L"true";
                } else {
                    msg = L"false";
                }
            }
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_UINT8: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_INT8: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_UINT16: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_INT16: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_UINT32: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_INT32: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_UINT64: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_INT64: {
        if (A.isScalar()) {
            msg = formatInteger(A.getDataPointer(), A.getDataClass(), 0, currentNumericFormat);
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_DOUBLE: {
        if (A.isSparse()) {
            msg = lightDescription(A, L"[", L"]");
        } else {
            if (A.isScalar()) {
                double value = *(static_cast<const double*>(A.getDataPointer()));
                msg = formatScalarNumber(value, false, currentNumericFormat, true);
                if (currentNumericFormat == NLS_NUMERIC_FORMAT_RATIONAL) {
                    size_t nbCharsLimit = 6;
                    if (boost::contains(msg, L"/")) {
                        nbCharsLimit++;
                    }
                    if (boost::contains(msg, L"-")) {
                        nbCharsLimit++;
                    }
                    if (msg.length() > nbCharsLimit) {
                        msg = L"*";
                    }
                }
                if (currentNumericFormat == NLS_NUMERIC_FORMAT_BANK) {
                    if (msg.length() > termWidth) {
                        msg = lightDescription(A, L"", L"");
                    }
                }
            } else {
                msg = lightDescription(A, L"[", L"]");
            }
        }
    } break;
    case NLS_DCOMPLEX: {
        if (A.isSparse()) {
            msg = lightDescription(A, L"[", L"]");
        } else {
            if (A.isScalar()) {
                const auto* ap = static_cast<const double*>(A.getDataPointer());
                msg = formatScalarComplexNumber(ap[0], ap[1], false, currentNumericFormat, true);
                if (currentNumericFormat == NLS_NUMERIC_FORMAT_BANK) {
                    if (msg.length() > termWidth) {
                        msg = lightDescription(A, L"", L"");
                    }
                }
            } else {
                msg = lightDescription(A, L"[", L"]");
            }
        }
    } break;
    case NLS_SINGLE: {
        if (A.isScalar()) {
            single value = *(static_cast<const single*>(A.getDataPointer()));
            msg = formatScalarNumber((double)value, true,currentNumericFormat, true);
            if (currentNumericFormat == NLS_NUMERIC_FORMAT_RATIONAL) {
                size_t nbCharsLimit = 6;
                if (boost::contains(msg, L"/")) {
                    nbCharsLimit++;
                }
                if (boost::contains(msg, L"-")) {
                    nbCharsLimit++;
                }
                if (msg.length() > nbCharsLimit) {
                    msg = L"*";
                }
            }
            if (currentNumericFormat == NLS_NUMERIC_FORMAT_BANK) {
                if (msg.length() > termWidth) {
                    msg = lightDescription(A, L"", L"");
                }
            }
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    case NLS_SCOMPLEX: {
        if (A.isScalar()) {
            const single* ap = static_cast<const single*>(A.getDataPointer());
            msg = formatScalarComplexNumber(
                (double)ap[0], (double)ap[1], true, currentNumericFormat, true);
            if (currentNumericFormat == NLS_NUMERIC_FORMAT_BANK) {
                if (msg.length() > termWidth) {
                    msg = lightDescription(A, L"", L"");
                }
            }
        } else {
            msg = lightDescription(A, L"[", L"]");
        }
    } break;
    default: {
    } break;
    }
    return msg;
}
//=============================================================================
std::wstring
lightDescription(const ArrayOf& A, const std::wstring& firstChar, const std::wstring& lastChar)
{
    std::wstring format = L"%s%s %s%s";
    return fmt::sprintf(
        format, firstChar, A.getDimensions().toWideString(), getClassAsWideString(A), lastChar);
}
//=============================================================================
std::wstring
columnsHeader(indexType startCol, indexType endCol)
{
    std::wstring msg;
    if (startCol == endCol) {
        msg = fmt::sprintf(_W("  Columns %d"), startCol);
    } else {
        msg = fmt::sprintf(_W("  Columns %d through %d"), startCol, endCol);
    }
    return msg;
}
//=============================================================================
} // namespace Nelson
//=============================================================================
