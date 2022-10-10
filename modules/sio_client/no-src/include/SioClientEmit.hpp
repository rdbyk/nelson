//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// SPDX-License-Identifier: LGPL-3.0-or-later
// LICENCE_BLOCK_END
//=============================================================================
#pragma once
//=============================================================================
#include <string>
#include "nlsSio_client_exports.h"
//=============================================================================
namespace Nelson {
//=============================================================================
NLSSIO_CLIENT_IMPEXP void
sioemit(const std::string& name, const std::string& message);
//=============================================================================
};
//=============================================================================
