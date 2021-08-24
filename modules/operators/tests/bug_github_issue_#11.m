%=============================================================================
% Copyright (c) 2017 Allan CORNET (Nelson)
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
% <-- Issue URL -->
% https://github.com/Nelson-numerical-software/nelson/issues/11
% <-- Short Description -->
% colon constructor failed with some special values
%=============================================================================
V = [0. : 0.1 : 0.6];
assert_isequal(size(V), [1 7])
REF = [0.00000  0.10000  0.20000  0.30000  0.40000  0.50000  0.60000];
assert_isapprox(V, REF, 1e-5);
%=============================================================================
V = [0. : 0.2 : 0.6];
assert_isequal(size(V), [1 4])
REF = [0    0.2000    0.4000    0.6000];
assert_isapprox(V, REF, 1e-5);
%=============================================================================
V = [0. : 0.12 : 0.55];
assert_isequal(size(V), [1 5])
REF = [0    0.1200    0.2400    0.3600    0.4800];
assert_isapprox(V, REF, 1e-5);
%=============================================================================