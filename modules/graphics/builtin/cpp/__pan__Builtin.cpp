//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// SPDX-License-Identifier: LGPL-3.0-or-later
// LICENCE_BLOCK_END
//=============================================================================
#include "__pan__Builtin.hpp"
#include "Error.hpp"
#include "i18n.hpp"
#include "InputOutputArgumentsCheckers.hpp"
#include "GraphicsObject.hpp"
#include "GOHelpers.hpp"
#include "GOPropertyValues.hpp"
#include "GOPropertyNames.hpp"
#include "GOAxis.hpp"
#include "GOFiguresManager.hpp"
#include "axesBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
namespace Nelson::GraphicsGateway {
//=============================================================================
static void
panOption(GOAxis* axis, const std::wstring& option);
//=============================================================================
ArrayOfVector
__pan__Builtin(int nLhs, const ArrayOfVector& argIn)
{
    nargincheck(argIn, 2, 2);
    nargoutcheck(nLhs, 0, 0);

    // __pan__(ax, 'on' | 'off' | 'xon' | 'yon' | 'toggle')

    if (!argIn[0].isGraphicsObject()) {
        Error(_W("Expected graphics object(s)."));
    }
    int64 handle = argIn[0].getContentAsGraphicsObjectScalar();

    bool isAxis = false;
    GraphicsObject* fp = nullptr;
    if (handle >= HANDLE_OFFSET_OBJECT) {
        fp = findGraphicsObject(handle);
        if (fp->getType() == GO_PROPERTY_VALUE_AXES_STR) {
            isAxis = true;
        }
    }
    if (!isAxis) {
        Error(_W("Axes graphic object expected."));
    }
    GOAxis* axis = (GOAxis*)fp;

    std::wstring option = L"toggle";
    if (argIn.size() == 1) {
        if (argIn[1].isRowVectorCharacterArray() || argIn[1].isScalarStringArray()) {
            option = argIn[1].getContentAsWideString();
        } else {
            Error(_W("wrong type for #2 argument."));
        }
    }
    panOption(axis, option);
    return {};
}
//=============================================================================
void
panOption(GOAxis* axis, const std::wstring& option)
{
    if (option == L"on") {
        GOFigure* goFig = axis->getParentFigure();
        GOWindow* goWin = goFig->getGOWindow();
        if (goWin->getCurrentMouseMode() != MOUSE_MODE::PAN) {
            goWin->onPanAction();
        }
        axis->panOn();
    } else if (option == L"off") {
        GOFigure* goFig = axis->getParentFigure();
        GOWindow* goWin = goFig->getGOWindow();
        if (goWin->getCurrentMouseMode() == MOUSE_MODE::PAN) {
            goWin->onPanAction();
        }
        axis->panOff();
    } else if (option == L"xon") {
        GOFigure* goFig = axis->getParentFigure();
        GOWindow* goWin = goFig->getGOWindow();
        if (goWin->getCurrentMouseMode() != MOUSE_MODE::PAN) {
            goWin->onPanAction();
        }
        axis->panXMode();
    } else if (option == L"yon") {
        GOFigure* goFig = axis->getParentFigure();
        GOWindow* goWin = goFig->getGOWindow();
        if (goWin->getCurrentMouseMode() != MOUSE_MODE::PAN) {
            goWin->onPanAction();
        }
        axis->panYMode();
    } else if (option == L"toggle") {
        GOFigure* goFig = axis->getParentFigure();
        GOWindow* goWin = goFig->getGOWindow();
        goWin->onPanAction();
    }
}
//=============================================================================
}
//=============================================================================
