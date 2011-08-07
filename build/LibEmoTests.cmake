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


include ("LibEmoUnitTests.cmake")


#
# Include tests if allowed
#

if (NOT DEFINED EMO_DISABE_ALL_TESTS OR NOT EMO_DISABE_ALL_TESTS)
    # Force local version of libEmo to use for tests.
    set (LIBEMO_FORCE_HINTS TRUE)
    # Extend modules path with local modules.
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${EMO_CMAKE_DIR}")
    #

    # Add tests infrastructure.
    add_subdirectory ("${EMO_TESTS_DIR}" "${EMO_BUILD_DIR}/tests")
endif (NOT DEFINED EMO_DISABE_ALL_TESTS OR NOT EMO_DISABE_ALL_TESTS)


