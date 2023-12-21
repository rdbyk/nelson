%=============================================================================
% Copyright (c) 2016-present Allan CORNET (Nelson)
%=============================================================================
% This file is part of the Nelson.
%=============================================================================
% LICENCE_BLOCK_BEGIN
% SPDX-License-Identifier: LGPL-3.0-or-later
% LICENCE_BLOCK_END
%=============================================================================
% <--SEQUENTIAL TEST REQUIRED-->
%=============================================================================
clear('all')
[u1, s1] = memory();
%=============================================================================
addpath([modulepath('stream_manager', 'tests'), '/loadsavebin']);
for i=1:50000
  typeofbin(201);
end
%=============================================================================
sleep(5);
%=============================================================================
% it is not a good practice to compare memory because mac, linux, win have not same behavior. 
%=============================================================================
[u2, s2] = memory();
r = u2.MemUsedNelson - u1.MemUsedNelson;
disp(r)
if ispc()
  assert_istrue(r < 630000)
else
  assert_istrue(r < 6300000)
end
%=============================================================================
