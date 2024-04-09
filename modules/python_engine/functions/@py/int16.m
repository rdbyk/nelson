%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
function r = int16(obj)
  if ismethod(obj, 'int16')
    r = obj.int16();
  else
    error([_('Wrong value for #2 argument.'), ' ', 'int16']);
  end
end
%=============================================================================
