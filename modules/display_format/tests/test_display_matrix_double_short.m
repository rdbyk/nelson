%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% This program is free software; you can redistribute it and/or
% modify it under the terms of the GNU Lesser General Public
% License as published by the Free Software Foundation; either
% version 2.1 of the License, or (at your option) any later version.
%
% Alternatively, you can redistribute it and/or
% modify it under the terms of the GNU General Public License as
% published by the Free Software Foundation; either version 2 of
% the License, or (at your option) any later version.
%
% This program is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU Lesser General Public License for more details.
%
% You should have received a copy of the GNU Lesser General Public
% License along with this program. If not, see <http://www.gnu.org/licenses/>.
% LICENCE_BLOCK_END
%=============================================================================
format('short')
%=============================================================================
R = evalc('A = [1e9 1e99]');
REF =  '
A =

   1.0e+99 *

    0.0000    1.0000

';
assert_isequal(R, REF)
%=============================================================================
R = evalc('A = [6.5574e-04, 6.5574e-04]');
REF =     '
A =

   1.0e-03 *

    0.6557    0.6557

';
assert_isequal(R, REF)
%=============================================================================
R = evalc('A = [0.3729   6.5574e-04    0.1393]');
REF ='
A =

    0.3729    0.0007    0.1393

';
assert_isequal(R, REF)
%=============================================================================
R = evalc('A = eye(3,3) * eps');
REF = '
A =

   1.0e-15 *

    0.2220         0         0
         0    0.2220         0
         0         0    0.2220

';
assert_isequal(R, REF)
%=============================================================================
A = [0.2220, 1, 2;
     0,  0.2220, 4;
     5, 6, 0.2220];
R = evalc('A');
REF = '
A =

    0.2220    1.0000    2.0000
         0    0.2220    4.0000
    5.0000    6.0000    0.2220

';
assert_isequal(R, REF)
%=============================================================================