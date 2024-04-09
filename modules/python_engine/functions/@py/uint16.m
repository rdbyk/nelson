%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
function r = uint16(obj)
  if ismethod(obj, 'uint16')
    r = obj.uint16();
  else
    error([_('Wrong value for #2 argument.'), ' ', 'uint16']);
  end
end
%=============================================================================
