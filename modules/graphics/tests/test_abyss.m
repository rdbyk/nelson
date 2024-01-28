%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
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
surf(peaks);
colormap('abyss');
r = f.Colormap;
assert_isapprox(r(1:2, :), [0.0372, 0.1373, 0.2167; 0.0377, 0.1389, 0.2192], 1e-3); 
%=============================================================================
