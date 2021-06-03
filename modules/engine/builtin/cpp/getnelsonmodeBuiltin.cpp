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
#include "getnelsonmodeBuiltin.hpp"
#include "Error.hpp"
#include "NelSon_engine_mode.h"
//=============================================================================
using namespace Nelson;
//=============================================================================
ArrayOfVector
Nelson::EngineGateway::getnelsonmodeBuiltin(Evaluator* eval, int nLhs, const ArrayOfVector& argIn)
{
    ArrayOfVector retval;
    nargincheck(argIn, 0, 0);
    nargoutcheck(nLhs, 0, 1);
    auto _mode = static_cast<NELSON_ENGINE_MODE>(eval->getNelsonEngineMode());
    switch (_mode) {
    case BASIC_ENGINE: {
        retval << ArrayOf::characterArrayConstructor("BASIC_ENGINE");
    } break;
    case ADVANCED_ENGINE: {
        retval << ArrayOf::characterArrayConstructor("ADVANCED_ENGINE");
    } break;
    case BASIC_TERMINAL: {
        retval << ArrayOf::characterArrayConstructor("BASIC_TERMINAL");
    } break;
    case ADVANCED_TERMINAL: {
        retval << ArrayOf::characterArrayConstructor("ADVANCED_TERMINAL");
    } break;
    case BASIC_SIO_CLIENT: {
        retval << ArrayOf::characterArrayConstructor("BASIC_SIO_CLIENT");
    } break;
    case ADVANCED_SIO_CLIENT: {
        retval << ArrayOf::characterArrayConstructor("ADVANCED_SIO_CLIENT");
    } break;
    case GUI: {
        retval << ArrayOf::characterArrayConstructor("GUI");
    } break;
    default: {
        Error(_W("unknown mode."));
    } break;
    }
    return retval;
}
//=============================================================================
