%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
R = db2mag(mag2db(pi));
REF = pi;
assert_isapprox(R, REF, 1e-4);
%=============================================================================
R =  db2mag(NaN);
REF = NaN;
assert_isequal(R, REF);
%=============================================================================
M = [ 18.0618         0   15.5630;
9.5424   13.9794   16.9020;
12.0412   19.0849    6.0206];
R =  db2mag(M);
REF = magic(3);
assert_isapprox(R, REF, 1e-3);
%=============================================================================
