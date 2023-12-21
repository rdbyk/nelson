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
f = figure();
sys = tf(4,[1 2 10]);
impulse(sys)
%=============================================================================
sys = tf(4,[1 2 10]);
t = 0:0.05:5;
y = impulse(sys,t);
assert_isequal(size(y), [101, 1]);
f = figure();
impulse(sys,t);
%=============================================================================
