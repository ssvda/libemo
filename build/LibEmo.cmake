################################################################################
# Embeded Meta Objects (EMO) Library
#
# Copyright (C) 2011  Dmitry A. Sysoev
# Copyright (C) 2011  Yuri O. Nuzhdin
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
################################################################################

#
# Define variables with different places.
#

# Test for current location.
get_filename_component(EMO_CMAKE_RUN_FROM "${CMAKE_BINARY_DIR}" NAME)
# We _must_ run cmake only from build subdirectory of project.
if (NOT ("${EMO_CMAKE_RUN_FROM}" STREQUAL "build"))
	message (FATAL_ERROR "You _must_ run cmake only from `build' directory.")
endif (NOT ("${EMO_CMAKE_RUN_FROM}" STREQUAL "build"))

# Emo sources root directory.
if (NOT DEFINED EMO_ROOT_DIR)
	get_filename_component(EMO_ROOT_DIR ${EMO_SOURCE_DIR}/.. ABSOLUTE)
endif (NOT DEFINED EMO_ROOT_DIR)

# General directories.
set (EMO_SRC_DIR    ${EMO_ROOT_DIR}/libemo)
set (EMO_HEADER_DIR ${EMO_ROOT_DIR}/include)
set (EMO_DOC_DIR    ${EMO_ROOT_DIR}/doc)
set (EMO_TESTS_DIR  ${EMO_ROOT_DIR}/tests)
set (EMO_CMAKE_DIR  ${EMO_ROOT_DIR}/mkspec/cmake)
set (EMO_BUILD_DIR  ${EMO_ROOT_DIR}/build)

#
# Setup hints for FindLibEmo.cmake
#

set(EMO_HINT_INCLUDEDIR ${EMO_HEADER_DIR})
set(EMO_HINT_LIBRARY ${EMO_BUILD_DIR}/libemo)

#
# Load LibEmo sources lists.
#

include (LibEmoFiles.cmake)

#
# Form sources lists with full absolute pathes.
#

macro (EmoInternBuildFullPathedList TARGET_VAR SOURCE_VAR PREFIX_DIR)
	foreach (EMO_INTERN_FILENAME ${${SOURCE_VAR}})
		list (APPEND ${TARGET_VAR} "${PREFIX_DIR}/${EMO_INTERN_FILENAME}")
	endforeach (EMO_INTERN_FILENAME)
endmacro (EmoInternBuildFullPathedList)

# Form list of c-style headers.
EmoInternBuildFullPathedList (EMO_CSTYLE_HEADERS EMO_CSTYLE_HEADERS_LIST "${EMO_HEADER_DIR}")
# Form list of Qt-style headers.
EmoInternBuildFullPathedList (EMO_QTSTYLE_HEADERS EMO_QTSTYLE_HEADERS_LIST "${EMO_HEADER_DIR}")
# Form full list of headers.
set (EMO_HEADERS ${EMO_CSTYLE_HEADERS} ${EMO_QTSTYLE_HEADERS})

# From list of sources.
EmoInternBuildFullPathedList (EMO_SOURCES EMO_SOURCES_LIST "${EMO_SRC_DIR}")

# Form list of Doxygen documentation for sources.
EmoInternBuildFullPathedList (EMO_SOURCES_DOX EMO_SOURCES_DOX_LIST "${EMO_DOC_DIR}")
# Form list of general Doxygen documentation.
EmoInternBuildFullPathedList (EMO_GENERAL_DOX EMO_GENERAL_DOX_LIST "${EMO_DOC_DIR}")
# Form list of Doxygen documentation.
set (EMO_DOX ${EMO_SOURCES_DOX} ${EMO_GENERAL_DOX})

#
# LibEmo target.
#

add_library (Emo
	${EMO_HEADERS}
	${EMO_SOURCES}
)

#
# Documentation target.
#

# List of all avaible languages.
# TODO Possible need to move it somewhere?
if (NOT DEFINED EMO_DOX_LANGUAGES)
	set (EMO_DOX_LANGUAGES
		English
		Russian
	)
endif (NOT DEFINED EMO_DOX_LANGUAGES)

# Clear list of dependences.
set (EMO_DOX_LANGUAGES_DEPS)
# Clear list for config files.
set (EMO_DOX_CONFIGS)
# Clear list for config files.
set (EMO_DOX_LANGUAGES_DIRS)

# Create output directory.
execute_process (
	COMMAND "${CMAKE_COMMAND}" -E make_directory "${EMO_ROOT_DIR}/doxygen"
)

# Add target for documentation for each language in list.
foreach (EMO_INTERN_LANG ${EMO_DOX_LANGUAGES})
	execute_process (
		COMMAND "${CMAKE_COMMAND}" -E make_directory "${EMO_ROOT_DIR}/doxygen/${EMO_INTERN_LANG}"
	)
	file (READ "${EMO_ROOT_DIR}/Doxyfile" EMO_INTERN_DOXYFILE)
	string (REGEX REPLACE
		"OUTPUT_LANGUAGE[^\n\r]*\r?[\n\r]"
		"OUTPUT_LANGUAGE = ${EMO_INTERN_LANG}\n"
		EMO_INTERN_DOXYFILE
		"${EMO_INTERN_DOXYFILE}"
	)
	string (REGEX REPLACE
		"OUTPUT_DIRECTORY[^\n\r]*\r?[\n\r]"
		"OUTPUT_DIRECTORY = doxygen/${EMO_INTERN_LANG}\n"
		EMO_INTERN_DOXYFILE
		"${EMO_INTERN_DOXYFILE}"
	)
	file (WRITE "${EMO_ROOT_DIR}/Doxyfile.${EMO_INTERN_LANG}" "${EMO_INTERN_DOXYFILE}")
	add_custom_target(doc.${EMO_INTERN_LANG}
		COMMAND doxygen "${EMO_ROOT_DIR}/Doxyfile.${EMO_INTERN_LANG}"
		WORKING_DIRECTORY "${EMO_ROOT_DIR}"
		DEPENDS "${EMO_ROOT_DIR}/Doxyfile" ${EMO_DOX}
	)
	list (APPEND EMO_DOX_LANGUAGES_DEPS doc.${EMO_INTERN_LANG})
	list (APPEND EMO_DOX_CONFIGS "${EMO_ROOT_DIR}/Doxyfile.${EMO_INTERN_LANG}")
endforeach (EMO_INTERN_LANG)

# Add target for all languages.
add_custom_target(doc
	DEPENDS ${EMO_DOX_LANGUAGES_DEPS}
	SOURCES "${EMO_ROOT_DIR}/Doxyfile" ${EMO_DOX}
)

#
# Special distclean target.
#

add_custom_target(distclean
	COMMAND "${CMAKE_COMMAND}" -E remove -f ${EMO_DOX_CONFIGS}
	COMMAND "${CMAKE_COMMAND}" -E remove_directory "${EMO_ROOT_DIR}/CMakeFiles"
	COMMAND "${CMAKE_COMMAND}" -E remove -f "${EMO_ROOT_DIR}/CMakeCache.txt"
	COMMAND "${CMAKE_COMMAND}" -E remove_directory "${EMO_BUILD_DIR}/build"
	COMMAND "${CMAKE_COMMAND}" -E remove_directory "${EMO_BUILD_DIR}/CMakeFiles"
	COMMAND "${CMAKE_COMMAND}" -E remove_directory "${EMO_BUILD_DIR}/tests"
	COMMAND "${CMAKE_COMMAND}" -E remove -f "${EMO_BUILD_DIR}/CMakeCache.txt"
	COMMAND "${CMAKE_COMMAND}" -E remove -f "${EMO_BUILD_DIR}/cmake_install.cmake"
	COMMAND "${CMAKE_COMMAND}" -E remove -f "${EMO_BUILD_DIR}/Makefile"
)

#
# Tests support.
#

macro (add_emo_test TEST_NAME)
	set (EMO_INTERN_TEST_DISABLED FALSE)
	foreach (EMO_INTERN_TEST ${EMO_DISABE_TESTS})
		if (${EMO_INTERN_TEST} STREQUAL ${TEST_NAME})
			set (EMO_INTERN_TEST_DISABLED TRUE)
			break ()
		endif (${EMO_INTERN_TEST} STREQUAL ${TEST_NAME})
	endforeach (EMO_INTERN_TEST)
	
	if (NOT EMO_INTERN_TEST_DISABLED)
		add_subdirectory (${TEST_NAME})
	endif (NOT EMO_INTERN_TEST_DISABLED)
endmacro (add_emo_test)

macro (build_after_libemo TEST_NAME)
	add_dependencies (${TEST_NAME} Emo)
endmacro (build_after_libemo)

macro (build_project_after_libemo)
	add_dependencies (${PROJECT_NAME} Emo)
endmacro (build_project_after_libemo)

if (NOT DEFINED EMO_DISABE_ALL_TESTS OR NOT EMO_DISABE_ALL_TESTS)
	# Force local version of libEmo to use for tests.
	set (LIBEMO_FORCE_HINTS TRUE)
	# Extend modules path with local modules.
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${EMO_CMAKE_DIR}")
	#
	
	# Add tests infrastructure.
	add_subdirectory ("${EMO_TESTS_DIR}" "${EMO_BUILD_DIR}/tests")
endif (NOT DEFINED EMO_DISABE_ALL_TESTS OR NOT EMO_DISABE_ALL_TESTS)
