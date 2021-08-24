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
DESTINATION = [nelsonroot(), '/module_skeleton'];
if isdir(DESTINATION)
  rmdir(DESTINATION, 's');
end
mkdir(DESTINATION);

URL = 'https://github.com/Nelson-numerical-software/module_skeleton.git';
try
  repo('clone', URL, DESTINATION);
  bSuccess = true;
catch
  bSuccess = false;
end
if ~bSuccess
  try
    unix(['git clone ', URL, ' ', DESTINATION]);
    bSuccess = true;
  catch
    bSuccess = false;
  end
end
if isdir([DESTINATION, '/.git'])
  rmdir([DESTINATION, '/.git'], 's');
end
exit();
%=============================================================================