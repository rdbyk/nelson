%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
function varargout = methods(varargin)
  narginchk(1, 1);
  nargoutchk(0, 1);
  obj = varargin{1};
  if ~isa(obj, 'DisplayFormatOptions')
    error(_('''DisplayFormatOptions'' class expected.'));
  end
  varargout = {};
  if nargout == 1
    varargout{1} = {'DisplayFormatOptions'};
    return
  end
  fmt = format();
  LineSpacing = fmt.LineSpacing;
  if strcmp(LineSpacing, 'loose')
    fprintf('\n')
  end
  msg = sprintf(_('Methods for class %s:\n'), class(obj));
  fprintf(msg)
  if strcmp(LineSpacing, 'loose')
    fprintf('\n')
  end
  for e = {'DisplayFormatOptions'}
    fprintf('    %s\n', e{1});
  end
  if strcmp(LineSpacing, 'loose')
    fprintf('\n')
  end
end
