%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
x = [-2, -1, 0, 1, 2];
R = normpdf(x);
REF =  [0.0540    0.2420    0.3989    0.2420    0.0540];
assert_isapprox(R, REF, 1e-3);
%=============================================================================
x = [-2, -1, 0, 1, 2];
R = normpdf(x, 2, 1);
REF = [0.0001    0.0044    0.0540    0.2420    0.3989];
assert_isapprox(R, REF, 1e-3);
%=============================================================================
R = normpdf(0, [-2, -1, 0, 1, 2], 1);
REF = [  0.0540    0.2420    0.3989    0.2420    0.0540];
assert_isapprox(R, REF, 1e-3);
%=============================================================================
