;==============================================================================
; Copyright (c) 2016-present Allan CORNET (Nelson)
;==============================================================================
; This file is part of the Nelson.
;==============================================================================
; LICENCE_BLOCK_BEGIN
; SPDX-License-Identifier: LGPL-3.0-or-later
; LICENCE_BLOCK_END
;==============================================================================
Source: {#RootPath}modules\modules.m; DestDir: {app}\modules\; AfterInstall: AfterNelsonInstall();
;==============================================================================
#include "main/module.iss"
#include "characters_encoding/module.iss"
#include "commons/module.iss"
#include "nelson_manager/module.iss"
#include "terminal/module.iss"
#include "operators/module.iss"
#include "elementary_mathematics/module.iss"
#include "dynamic_link/module.iss"
#include "modules_manager/module.iss"
#include "engine/module.iss"
#include "functions_manager/module.iss"
#include "core/module.iss"
#include "localization/module.iss"
#include "i18n/module.iss"
#include "string/module.iss"
#include "error_manager/module.iss"
#include "overload/module.iss"
#include "function_handle/module.iss"
#include "constructors_functions/module.iss"
#include "types/module.iss"
#include "single/module.iss"
#include "double/module.iss"
#include "data_structures/module.iss"
#include "integer/module.iss"
#include "elementary_functions/module.iss"
#include "data_analysis/module.iss"
#include "special_functions/module.iss"
#include "trigonometric_functions/module.iss"
#include "sparse/module.iss"
#include "logical/module.iss"
#include "files_folders_functions/module.iss"
#include "os_functions/module.iss"
#include "memory_manager/module.iss"
#include "console/module.iss"
#include "stream_manager/module.iss"
#include "display_format/module.iss"
#include "interpreter/module.iss"
#include "debugger/module.iss"
#include "time/module.iss"
#include "random/module.iss"
#include "history_manager/module.iss"
#include "help_tools/module.iss"
#include "gui/module.iss"
#include "help_browser/module.iss"
#include "assert_functions/module.iss"
#include "tests_manager/module.iss"
#include "linear_algebra/module.iss"
#include "handle/module.iss"
#include "qml_engine/module.iss"
#include "com_engine/module.iss"
#include "fftw/module.iss"
#include "f2c/module.iss"
#include "nig/module.iss"
#include "slicot/module.iss"
#include "text_editor/module.iss"
#include "text_completion/module.iss"
#include "mpi/module.iss"
#include "json/module.iss"
#include "audio/module.iss"
#include "sio_client/module.iss"
#include "hdf5/module.iss"
#include "matio/module.iss"
#include "profiler/module.iss"
#include "file_archiver/module.iss"
#include "webtools/module.iss"
#include "graphics/module.iss"
#include "mex/module.iss"
#include "ipc/module.iss"
#include "statistics/module.iss"
#include "validators/module.iss"
#include "polynomial_functions/module.iss"
#include "parallel/module.iss"
#include "signal_processing/module.iss"
#include "geometry/module.iss"
#include "control_system/module.iss"
;==============================================================================
