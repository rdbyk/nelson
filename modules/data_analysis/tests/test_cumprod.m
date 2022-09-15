%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
assert_isequal(nargin('cumprod'), 4);
assert_isequal(nargout('cumprod'), 1);
%=============================================================================
R = cumprod([]);
REF = [];
assert_isequal(R, REF);
%=============================================================================
R = cumprod(Inf);
REF = Inf;
assert_isequal(R, REF);
%=============================================================================
A = 1:5;
R = cumprod(A);
REF = [1     2     6    24   120];
assert_isequal(R, REF);
%=============================================================================
A = single(1:5);
R = cumprod(A);
REF = single([1     2     6    24   120]);
assert_isequal(R, REF);
%=============================================================================
A = int8(1:5);
R = cumprod(A);
REF = int8([1     2     6    24   120]);
assert_isequal(R, REF);
%=============================================================================
A = [1 4 7; 2 5 8; 3 6 9];
R = cumprod(A);
REF = [  1     4     7;
2    20    56;
6   120   504];
assert_isequal(R, REF);
%=============================================================================
A = [1 3 5; 2 4 6];
R =  cumprod(A, 2);
REF = [1     3    15;
2     8    48];
assert_isequal(R, REF);
%=============================================================================
A = [true, false, true; true, true, false];
R = cumprod(A);
REF = [   1     0     1;1     0     0];
assert_isequal(R, REF);
%=============================================================================
A = [true, false, true; true, true, false];
R = cumprod(A, 2);
REF = [ 1     0     0; 1     1     0];
assert_isequal(R, REF);
assert_isequal(class(R), 'double');
%=============================================================================
A = [   9    10     3;10     7     6; 2     1    10];
R = cumprod(A,'forward')
REF = [     9    10     3; 90    70    18; 180    70   180];
assert_isequal(R, REF);
%=============================================================================
A = [   9    10     3;10     7     6; 2     1    10];
R = cumprod(A,'reverse')
REF = [ 180    70   180; 20     7    60;  2     1    10];
assert_isequal(R, REF);
%=============================================================================
A = [1 3 NaN 2 4 NaN];
R = cumprod(A);
REF = [  1     3   NaN   NaN   NaN   NaN];
assert_isequal(R, REF);
%=============================================================================
A = [1 3 NaN 2 4 NaN];
R = cumprod(A,'omitnan')
REF = [     1     3     3     6    24    24];
assert_isequal(R, REF);
%=============================================================================
A = [1 3 NaN 2 4 NaN];
R = cumprod(A,'includenan');
REF = [  1     3   NaN   NaN   NaN   NaN];
assert_isequal(R, REF);
%=============================================================================
A = int8([1 124; -127, 3]);
R = cumprod(A);
REF = int8([1   124; -127   127]);
assert_isequal(R, REF);
%=============================================================================
A = 1 + [   9    10     3;1     7     6; 2     1    1] * i;
R = cumprod(A);
REF = [  1 +  9i,    1 + 10i,    1 + 3i;
-8 + 10i,  -69 + 17i,  -17 + 9i;
-28 -  6i,  -86 - 52i,  -26 - 8i];
assert_isapprox(R, REF, 1e-4);
%=============================================================================