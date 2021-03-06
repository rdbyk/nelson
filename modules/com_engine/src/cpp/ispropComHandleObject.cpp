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
#include "ispropComHandleObject.hpp"
#include "ComHandleObject.hpp"
#include "ComHelpers.hpp"
#include "Exception.hpp"
#include "HandleManager.hpp"
#include "characters_encoding.hpp"
#include <Windows.h>
//=============================================================================
namespace Nelson {
//=============================================================================
bool
ispropComHandleObject(ComHandleObject* comhandleobj, const std::wstring& propertyName)
{
    void* ptr = comhandleobj->getPointer();
    if (ptr == nullptr) {
        throw Exception(_W("COM valid handle expected."));
    }
    VARIANT* pVariant = (VARIANT*)ptr;
    return isPropertyGetCom(pVariant->pdispVal, propertyName)
        || isPropertyPutCom(pVariant->pdispVal, propertyName);
}
//=============================================================================
ArrayOf
ispropComHandleObject(ArrayOf A, const std::wstring& propertyName)
{
    if (A.getHandleCategory() != COM_CATEGORY_STR) {
        throw Exception(_W("COM handle expected."));
    }
    ComHandleObject* comhandleobj = (ComHandleObject*)A.getContentAsHandleScalar();
    bool res = ispropComHandleObject(comhandleobj, propertyName);
    return ArrayOf::logicalConstructor(res);
}
//=============================================================================
}
//=============================================================================
