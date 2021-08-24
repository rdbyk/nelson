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
assert_isequal(nargin('convertCharsToStrings'), -1);
assert_isequal(nargout('convertCharsToStrings'), -1);
%=============================================================================
[A, B, C, D] = convertCharsToStrings("one", 2, 'three', {'four' ; 'five'});
assert_isequal(A, "one");
assert_isequal(B, 2);
assert_isequal(C, "three");
assert_isequal(D, ["four"; "five"]);
%=============================================================================
[A, B, C, D] = convertCharsToStrings("one", 2, 'three', {'four' ; NaN ; 'five'});
assert_isequal(A, "one");
assert_isequal(B, 2);
assert_isequal(C, "three");
assert_isequal(D, {'four' ; NaN ; 'five'});
%=============================================================================
[A, B, C, D] = convertCharsToStrings("one", 2, 'three', {'four' ; 'NaN' ;'five'});
assert_isequal(A, "one");
assert_isequal(B, 2);
assert_isequal(C, "three");
assert_isequal(D, ["four"; "NaN"; "five"]);
%=============================================================================
R = convertCharsToStrings(char(ones(0,3)));
assert_isequal(R, "");
%=============================================================================
R = convertCharsToStrings({});
assert_isequal(R, string([]));
%=============================================================================
R = convertCharsToStrings(['Nelson' ; '  is  '; '  good']);
assert_isequal(R, string('Nelson  is    good'));
%=============================================================================