//=============================================================================
// Copyright (c) 2016-present Allan CORNET (Nelson)
//=============================================================================
// This file is part of the Nelson.
//=============================================================================
// LICENCE_BLOCK_BEGIN
// SPDX-License-Identifier: LGPL-3.0-or-later
// LICENCE_BLOCK_END
//=============================================================================
#include "IJVBuiltin.hpp"
#include "NelsonGateway.hpp"
#include "fullBuiltin.hpp"
#include "nnzBuiltin.hpp"
#include "nzmaxBuiltin.hpp"
#include "sparseBuiltin.hpp"
#include "sparsedouble_horzcatBuiltin.hpp"
#include "sparsedouble_imagBuiltin.hpp"
#include "sparsedouble_realBuiltin.hpp"
#include "sparsedouble_vertcatBuiltin.hpp"
#include "sparselogical_horzcatBuiltin.hpp"
#include "sparselogical_imagBuiltin.hpp"
#include "sparselogical_realBuiltin.hpp"
#include "sparselogical_vertcatBuiltin.hpp"
//=============================================================================
using namespace Nelson;
//=============================================================================
const std::wstring gatewayName = L"sparse";
//=============================================================================
static const nlsGateway gateway[] = {
    { "sparse", (ptrBuiltin)Nelson::SparseGateway::sparseBuiltin, 1, 6 },
    { "full", (ptrBuiltin)Nelson::SparseGateway::fullBuiltin, 1, 1 },
    { "sparselogical_real", (ptrBuiltin)Nelson::SparseGateway::sparselogical_realBuiltin, 1, 1,
        CPP_BUILTIN_WITH_EVALUATOR },
    { "sparselogical_imag", (ptrBuiltin)Nelson::SparseGateway::sparselogical_imagBuiltin, 1, 1,
        CPP_BUILTIN_WITH_EVALUATOR },
    { "sparsedouble_real", (ptrBuiltin)Nelson::SparseGateway::sparsedouble_realBuiltin, 1, 1,
        CPP_BUILTIN_WITH_EVALUATOR },
    { "sparsedouble_imag", (ptrBuiltin)Nelson::SparseGateway::sparsedouble_imagBuiltin, 1, 1,
        CPP_BUILTIN_WITH_EVALUATOR },
    { "IJV", (ptrBuiltin)Nelson::SparseGateway::IJVBuiltin, -1, 1, CPP_BUILTIN_WITH_EVALUATOR },
    { "sparselogical_vertcat", (ptrBuiltin)Nelson::SparseGateway::sparselogical_vertcatBuiltin, 1,
        2 },
    { "sparselogical_horzcat", (ptrBuiltin)Nelson::SparseGateway::sparselogical_horzcatBuiltin, 1,
        2, CPP_BUILTIN },
    { "sparsedouble_vertcat", (ptrBuiltin)Nelson::SparseGateway::sparsedouble_vertcatBuiltin, 1, 2,
        CPP_BUILTIN },
    { "sparsedouble_horzcat", (ptrBuiltin)Nelson::SparseGateway::sparsedouble_horzcatBuiltin, 1, 2,
        CPP_BUILTIN },
    { "nnz", (ptrBuiltin)Nelson::SparseGateway::nnzBuiltin, 1, 1 },
    { "nzmax", (ptrBuiltin)Nelson::SparseGateway::nzmaxBuiltin, 1, 1 },
};
//=============================================================================
NLSGATEWAYFUNC(gateway)
//=============================================================================
NLSGATEWAYINFO(gateway)
//=============================================================================
NLSGATEWAYREMOVE(gateway)
//=============================================================================
NLSGATEWAYNAME()
//=============================================================================
