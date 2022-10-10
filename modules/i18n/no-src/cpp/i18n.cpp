//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// SPDX-License-Identifier: LGPL-3.0-or-later
// LICENCE_BLOCK_END
//=============================================================================
#include "i18n.hpp"
#include "characters_encoding.hpp"
//=============================================================================
namespace Nelson {
//=============================================================================
std::wstring
gettextw(const std::wstring& S)
{
    return S;
}
//=============================================================================
std::wstring
gettextw(const std::string& S)
{
    return utf8_to_wstring(S);
}
//=============================================================================
std::string
gettext(const std::string& S)
{
    return S;
}
//=============================================================================
} // namespace Nelson
//=============================================================================
