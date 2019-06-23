#==============================================================================
# Copyright (c) 2016-present Allan CORNET (Nelson)
#==============================================================================
# This file is part of the Nelson.
#=============================================================================
# LICENCE_BLOCK_BEGIN
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# Alternatively, you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program. If not, see <http://www.gnu.org/licenses/>.
# LICENCE_BLOCK_END
#==============================================================================
set(module_name file_archiver)
set(module_library_name nlsFile_archiver)
set(module_library_builtin_name ${module_library_name}_builtin)
#==============================================================================
check_include_file(stdint.h   HAVE_STDINT_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
#==============================================================================
add_definitions(-DMZ_ZIP_NO_ENCRYPTION)
add_definitions(-DZLIB_COMPAT)
add_definitions(-DHAVE_ZLIB)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()
if(HAVE_INTTYPES_H)
    add_definitions(-DHAVE_INTTYPES_H)
endif()
#==============================================================================
include_directories(
${Boost_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../interpreter/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../types/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../stream_manager/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../error_manager/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../nelson_manager/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../elementary_functions/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../elementary_mathematics/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../characters_encoding/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../i18n/src/include
${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip
)
#==============================================================================	
FILE(
GLOB
FILE_ARCHIVER_SRC
"${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_compat.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_crypt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_os.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_os_posix.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm_os_posix.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm_buf.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm_mem.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm_split.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_strm_zlib.c"
"${CMAKE_CURRENT_SOURCE_DIR}/src/c/minizip/mz_zip.c"
)
#==============================================================================	
ADD_LIBRARY(
	${module_library_name}
	SHARED 
	${FILE_ARCHIVER_SRC}
)
#==============================================================================	
target_link_libraries(${module_library_name}
nlsInterpreter
nlsNelson_manager
nlsTypes
nlsElementary_functions
nlsElementary_mathematics
nlsCharacters_encoding
nlsI18n
${BOOST_LIBRARY}
${ZLIB_LIBRARIES} 
)
#==============================================================================	
set_target_properties(${module_library_name}
                      PROPERTIES 
                      VERSION ${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE} SOVERSION ${Nelson_VERSION_MAJOR})
#==============================================================================	
FILE(
GLOB
FILE_ARCHIVER_BUILTIN
"${CMAKE_CURRENT_SOURCE_DIR}/builtin/cpp/*.cpp"
)
#==============================================================================	
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/builtin/include
${CMAKE_CURRENT_SOURCE_DIR}/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../overload/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../api_nelson/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../i18n/src/include
${CMAKE_CURRENT_SOURCE_DIR}/../string/src/include
)
#==============================================================================	
ADD_LIBRARY(
	${module_library_builtin_name}
	SHARED 
	${FILE_ARCHIVER_BUILTIN}
)
#==============================================================================	
target_link_libraries(${module_library_builtin_name}
${module_library_name}
nlsError_manager
nlsInterpreter
nlsOverload
nlsTypes
nlsApi_nelson
nlsI18n
nlsString
${BOOST_LIBRARY}
)
#==============================================================================
set_target_properties(${module_library_builtin_name}
                      PROPERTIES 
                      VERSION ${Nelson_VERSION_MAJOR}.${Nelson_VERSION_MINOR}.${Nelson_VERSION_MAINTENANCE} SOVERSION ${Nelson_VERSION_MAJOR})
#==============================================================================	
install(TARGETS ${module_library_name} LIBRARY DESTINATION ${LIBRARY_OUTPUT})
install(TARGETS ${module_library_builtin_name} LIBRARY DESTINATION ${LIBRARY_OUTPUT})
install(FILES ${CMAKE_SOURCE_DIR}/modules/${module_name}/etc/startup.nls DESTINATION ${ROOT_OUTPUT}/modules/${module_name}/etc) 
install(FILES ${CMAKE_SOURCE_DIR}/modules/${module_name}/etc/finish.nls DESTINATION ${ROOT_OUTPUT}/modules/${module_name}/etc)
install(FILES ${CMAKE_SOURCE_DIR}/modules/${module_name}/loader.nls DESTINATION ${ROOT_OUTPUT}/modules/${module_name})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/modules/${module_name}/functions DESTINATION ${ROOT_OUTPUT}/modules/${module_name} FILES_MATCHING PATTERN "*.nlf")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/modules/${module_name}/help DESTINATION ${ROOT_OUTPUT}/modules/${module_name} FILES_MATCHING PATTERN "*.qch" PATTERN "xml" EXCLUDE PATTERN "md" EXCLUDE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/modules/${module_name}/tests DESTINATION ${ROOT_OUTPUT}/modules/${module_name} FILES_MATCHING PATTERN "*.nls")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/modules/${module_name}/tests DESTINATION ${ROOT_OUTPUT}/modules/${module_name} FILES_MATCHING PATTERN "*.zip")
#==============================================================================