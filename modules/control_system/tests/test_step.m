%=============================================================================
% Copyright (c) 2023-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
% <--ADV-CLI MODE-->
%=============================================================================
A = [-10 -20 -30;1  0  0; 0  1  0];
B = [1;   0;   0];
C = [0   0   1];
D = 0;
T = [0:0.1:1];
U = zeros(size(T, 1), size(T, 2));    
X0 = [0.1 0.1 0.1];
sys = ss(A, B, C, D);    
[x, t, y] = step(sys);

assert_isequal(size(x), [1001 1]);
assert_isequal(size(t), [1001 1]);
assert_isequal(size(y), [1001 3]);
assert_isapprox(x(1), 0, 1e-3);
assert_isapprox(x(end), 0.0333, 1e-2);
assert_isapprox(t(1), 0, 1e-3);
assert_isapprox(t(end), 10, 1e-3);
assert_isapprox(y(1, :), [0 0 0], 1e-3);
assert_isapprox(y(end, :),  [ -0.0000   -0.0000    0.0333], 1e-2);
%=============================================================================
step(sys);
%=============================================================================