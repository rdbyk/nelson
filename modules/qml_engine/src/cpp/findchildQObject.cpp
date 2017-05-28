//=============================================================================
// Copyright (c) 2016-2017 Allan CORNET (Nelson)
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
#include <QtQml/QQmlComponent>
#include "findchildQObject.hpp"
#include "HandleManager.hpp"
#include "QmlHandleObject.hpp"
#include "QStringConverter.hpp"
//=============================================================================
namespace Nelson {
    //=============================================================================
    ArrayOf findchildQObject(ArrayOf H, std::wstring fieldname, bool bRecursively)
    {
        ArrayOf res = ArrayOf::emptyConstructor(Dimensions(0, 0));
        res.promoteType(NLS_HANDLE);
        if (!H.isHandle())
        {
            throw Exception(ERROR_WRONG_ARGUMENT_1_TYPE_HANDLE_EXPECTED);
        }
        if (!H.isScalar())
        {
            throw Exception(ERROR_SIZE_SCALAR_EXPECTED);
        }
        nelson_handle *qp = (nelson_handle*)H.getDataPointer();
        if (qp == nullptr)
        {
            throw Exception(_W("QObject valid handle expected."));
        }
        nelson_handle hl = qp[0];
        HandleGenericObject *hlObj = HandleManager::getInstance()->getPointer(hl);
        if (hlObj == nullptr)
        {
            throw Exception(_W("QObject valid handle expected."));
        }
        if (hlObj->getCategory() != QOBJECT_CATEGORY_STR)
        {
            throw Exception(_W("QObject handle expected."));
        }
        QmlHandleObject *qmlhandleobj = (QmlHandleObject *)hlObj;
        void *ptr = qmlhandleobj->getPointer();
        if (ptr == nullptr)
        {
            throw Exception(_W("QObject valid handle expected."));
        }
        QObject *qobj = (QObject *)ptr;
        Qt::FindChildOption option = Qt::FindDirectChildrenOnly;
        if (bRecursively)
        {
            option = Qt::FindChildrenRecursively;
        }
        QObject *qobjfound = qobj->findChild<QObject*>(wstringToQString(fieldname), option);
        if (qobjfound != nullptr)
        {
            QmlHandleObject * qmlHandle = nullptr;
            try
            {
                qmlHandle = new QmlHandleObject(qobjfound);
            }
            catch (std::bad_alloc &e)
            {
                e.what();
                qmlHandle = nullptr;
                throw Exception(ERROR_MEMORY_ALLOCATION);
            }
            res = ArrayOf::handleConstructor(qmlHandle);
        }
        return res;
    }
    //=============================================================================
}
//=============================================================================
