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
% <--ADV-CLI MODE-->
% <--WITH DISPLAY-->
%=============================================================================
qml_file = [modulepath('qml_engine'), '/tests/test_qml_loadfile_window.qml'];
qobj1 = qml_loadfile(qml_file);
%=============================================================================
R1 = QObject_fieldnames(qobj1);
R2 = fieldnames(qobj1);
assert_isequal(R1, R2);
%=============================================================================
REF = { 'active'
'activeFocusItem'
'children'
'className'
'color'
'contentItem'
'contentOrientation'
'data'
'flags'
'height'
'maximumHeight'
'maximumWidth'
'minimumHeight'
'minimumWidth'
'modality'
'objectName'
'opacity'
'parent'
'title'
'visibility'
'visible'
'width'
'x'
'y'};
assert_istrue(any(contains(R1, REF)));
%=============================================================================