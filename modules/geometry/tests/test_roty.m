%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
R = roty(90);
REF =    [   0     0     1;     0     1     0;    -1     0     0];
assert_isequal(R, REF);
%=============================================================================
R = roty(180);
REF = [-1     0     0;     0     1     0;     0     0    -1];
assert_isequal(R, REF);
%=============================================================================
