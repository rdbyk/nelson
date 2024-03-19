%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
A = '123 Main St.';
R = isspace(A);
REF = logical([  0   0   0   1   0   0   0   0   1   0   0   0]);
assert_isequal(R, REF)
%=============================================================================
A = '123 Main St.';
B = [A; A];
R = isspace(B);
REF = logical([  0   0   0   1   0   0   0   0   1   0   0   0;   0   0   0   1   0   0   0   0   1   0   0   0]);
assert_isequal(R, REF)
%=============================================================================
A = "123 Main St.";
R = isspace(A);
REF = logical([  0   0   0   1   0   0   0   0   1   0   0   0]);
assert_isequal(R, REF)
%=============================================================================
A = '可口可乐; 可口可樂';
R = isspace(A);
REF = logical([0   0   0   0   0   1   0   0   0   0]);
assert_isequal(R, REF)
%=============================================================================
