//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// SPDX-License-Identifier: LGPL-3.0-or-later
// LICENCE_BLOCK_END
//=============================================================================
#define FMT_HEADER_ONLY
#include <fmt/printf.h>
#include <fmt/format.h>
#include <fmt/xchar.h>
#include "VertCat.hpp"
#include "Error.hpp"
#include "i18n.hpp"
#include "Operators.hpp"
#include "Evaluator.hpp"
#include "FindCommonType.hpp"
#include "OverloadHelpers.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
static ArrayOf
stringVertCat(const ArrayOfVector& v, NelsonType commonType);
static ArrayOf
cellVertCat(const ArrayOfVector& v, NelsonType commonType);
//=============================================================================
ArrayOf
Evaluator::vertcatOperator(const ArrayOfVector& v)
{
    ArrayOf res;
    switch (v.size()) {
    case 0: {
        res = ArrayOf::emptyConstructor();
    } break;
    case 1: {
        res = v[0];
    } break;
    default: {
        NelsonType commonType = NLS_DOUBLE;
        bool isSparse = false;
        bool isComplex = false;
        std::string commonTypeName = NLS_DOUBLE_STR;

        ArrayOf res;
        if (FindCommonConcatenateType(v, commonType, isSparse, isComplex, commonTypeName)) {
            bool overloadWasFound = false;
            res = callOverloadedFunction(
                this, v, VERTCAT_OPERATOR_STR, commonTypeName, commonType, overloadWasFound);
            if (overloadWasFound) {
                return res;
            }
        }
        if (isSparse
            && (commonType != NLS_DOUBLE && commonType != NLS_DCOMPLEX
                && commonType != NLS_LOGICAL)) {
            Error(_("Attempt to convert to unimplemented sparse type"), "Nelson:UnableToConvert");
        }
        switch (commonType) {
        case NLS_LOGICAL: {
            if (isSparse) {
                FunctionDef* funcDef = nullptr;
                std::string overloadTypeName
                    = overloadFunctionName(commonTypeName, VERTCAT_OPERATOR_STR);
                getContext()->lookupFunction(overloadTypeName, funcDef);
                if (funcDef) {
                    return funcDef->evaluateFunction(this, v, 1)[0];
                } else {
                    OverloadRequired(VERTCAT_OPERATOR_STR);
                }
            }
            return VertCat(v, commonType);
        } break;
        case NLS_DOUBLE:
        case NLS_DCOMPLEX: {
            if (isSparse) {
                FunctionDef* funcDef = nullptr;
                std::string overloadTypeName
                    = overloadFunctionName(commonTypeName, VERTCAT_OPERATOR_STR);
                getContext()->lookupFunction(overloadTypeName, funcDef);
                if (funcDef) {
                    return funcDef->evaluateFunction(this, v, 1)[0];
                } else {
                    OverloadRequired(VERTCAT_OPERATOR_STR);
                }
            }
            return VertCat(v, isComplex ? NLS_DCOMPLEX : NLS_DOUBLE);
        } break;
        case NLS_SINGLE:
        case NLS_SCOMPLEX: {
            return VertCat(v, isComplex ? NLS_SCOMPLEX : NLS_SINGLE);
        } break;
        case NLS_INT8:
        case NLS_INT16:
        case NLS_INT32:
        case NLS_INT64:
        case NLS_UINT8:
        case NLS_UINT16:
        case NLS_UINT32:
        case NLS_UINT64:
        case NLS_STRUCT_ARRAY:
        case NLS_CLASS_ARRAY:
        case NLS_GO_HANDLE: {
            return VertCat(v, commonType);
        } break;
        case NLS_CHAR: {
            if (isComplex) {
                Error(_("Complex values cannot be converted to chars."));
            }
            return VertCat(v, commonType);
        } break;
        case NLS_CELL_ARRAY: {
            return cellVertCat(v, commonType);
        } break;
        case NLS_STRING_ARRAY: {
            return stringVertCat(v, commonType);
        } break;
        case NLS_FUNCTION_HANDLE: {
            std::string msg = _(
                "Nonscalar arrays of function handles are not allowed; use cell arrays instead.");
            std::string id = "Nelson:err_non_scalar_function_handles";
            Error(msg, id);
        } break;
        case NLS_HANDLE: {
            bool overloadWasFound = false;
            res = callOverloadedFunction(
                this, v, VERTCAT_OPERATOR_STR, commonTypeName, commonType, overloadWasFound);
            if (!overloadWasFound) {
                OverloadRequired(VERTCAT_OPERATOR_STR);
            }
        } break;
        case NLS_UNKNOWN:
        default: {
            std::string msg
                = fmt::sprintf(_("Operator 'vertcat' is not supported for operands of type '%s'."),
                    ClassToString(commonType));
            Error(msg, "Nelson:UndefinedFunction");
        } break;
        }
    } break;
    }
    return res;
}
//=============================================================================
ArrayOf
stringVertCat(const ArrayOfVector& v, NelsonType commonType)
{
    ArrayOfVector _argIn(v);
    for (ompIndexType k = 0; k < (ompIndexType)v.size(); ++k) {
        if (!v[k].isStringArray()) {
            bool needOverload = false;
            _argIn[k] = ArrayOf::toStringArray(v[k], needOverload);
            if (needOverload) {
                Error(_W("Cannot promote to string array."));
            }
        } else {
            _argIn[k] = v[k];
        }
    }
    return VertCat(_argIn, commonType);
}
//=============================================================================
ArrayOf
cellVertCat(const ArrayOfVector& v, NelsonType commonType)
{
    ArrayOfVector _argIn;
    _argIn.reserve(v.size());
    for (auto k : v) {
        if (k.isEmpty()) {
            _argIn.push_back(k);
        } else {
            _argIn.push_back(ArrayOf::toCell(k));
        }
    }
    return VertCat(_argIn, commonType);
}
//=============================================================================
} // namespace Nelson
//=============================================================================
