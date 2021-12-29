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
date = {'1985-01-01';
'1985-01-09';
'1985-01-17';
'1985-01-25';
'1985-02-02';
'1985-02-10';
'1985-02-18';
'1985-02-26';
'1985-03-06';
'1985-03-14';
'1985-03-22';
'1985-03-30';
'1985-04-07';
'1985-04-15';
'1985-04-23';
'1985-05-01';
'1985-05-09';
'1985-05-17';
'1985-05-25';
'1985-06-02';
'1985-06-10';
'1985-06-18';
'1985-06-26';
'1985-07-04';
'1985-07-12';
'1985-07-20';
'1985-07-28';
'1985-08-05';
'1985-08-13';
'1985-08-21';
'1985-08-29';
'1985-09-06';
'1985-09-14';
'1985-09-22';
'1985-09-30';
'1985-10-08';
'1985-10-16';
'1985-10-24';
'1985-11-01';
'1985-11-09';
'1985-11-17';
'1985-11-25';
'1985-12-03';
'1985-12-11';
'1985-12-19';
'1985-12-27'};
filename = [tempdir(), 'earth.jpg'];
url = 'https://neo.gsfc.nasa.gov/wms/wms';
width = 1024;
height = 768;
html_line = ['<img src="', filename, '" width="', int2str(width), '" height="', int2str(height), '">'];

for k = date'
  destination_filename = websave(filename, url, 'Time', k{1}, 'Service','WMS','Layers','AVHRR_CLIM_W','CRS','CRS:84', 'Format','image/jpeg','Height', int2str(height), 'Width', int2str(width),  'BBOX','-180.0,-90.0,180.0,90.0','Version','1.3.0','Request','GetMap');
  clc;
  disp('Demo websave builtin: Average Sea Surface Temperature 1985-01-01 --> 1985-12-27')
  inserthtml(html_line);
  disp(k{1});
end
% download and display are not optimized here
% faster way should to download all images first :)
