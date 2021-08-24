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
assert_isequal(nargin('swapbytes'), 1)
assert_isequal(nargout('swapbytes'), 1)
%=============================================================================
R = swapbytes(0);
assert_isequal(R, 0);
%=============================================================================
R = swapbytes(NaN);
assert_isapprox(R, 3.1493e-319);
%=============================================================================
R2 = swapbytes(R);
assert_isequal(R2, NaN);
%=============================================================================
R = swapbytes(Inf);
assert_isapprox(R, 3.0418e-319);
%=============================================================================
R = swapbytes(single(1));
assert_isapprox(R, single(4.6006e-41));
%=============================================================================
R = swapbytes(single(4.6006e-41));
assert_isapprox(R, single(1));
%=============================================================================
assert_isequal(swapbytes(int8(8)),int8(8));
assert_isequal(swapbytes(uint8(8)),uint8(8));
%=============================================================================
assert_isequal(swapbytes(int16(8)),int16(2048));
assert_isequal(swapbytes(int16(-8)),int16(-1793));
%=============================================================================
assert_isequal(swapbytes(int32(1)),int32(16777216));
assert_isequal(swapbytes(int32(-1)),int32(-1));
%=============================================================================
assert_isequal(swapbytes(uint32(12)),uint32(201326592));
assert_isequal(swapbytes(uint32(68)),uint32(1140850688));
%=============================================================================
assert_isequal(swapbytes(int64(1)),int64(72057594037927936));
assert_isequal(swapbytes(int64(-1)),int64(-1));
%=============================================================================
assert_isequal(swapbytes(uint64(12)), uint64(864691128455135232));
assert_isequal(swapbytes(uint64(5648002115885334530u)),uint64(144115188088201550u));
%=============================================================================
R = swapbytes([1u, 2u, 3u; 4u, 5u, 6u]);
REF = [72057594037927936u, 144115188075855872u, 216172782113783808u;
 288230376151711744u, 360287970189639680u, 432345564227567616u];
assert_isequal(R, REF);
%=============================================================================
assert_checkerror('R = swapbytes(3+i);', sprintf(_('function %s_swapbytes undefined.'), 'double'));
%=============================================================================
assert_checkerror('R = swapbytes(true)', sprintf(_('function %s_swapbytes undefined.'), 'logical'));
%=============================================================================