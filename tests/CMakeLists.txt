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
# General settings.
#

# Minimal required version of cmake.
cmake_minimum_required (VERSION 2.6)
# Default cmake behaviour will be selected for compatibility with version 2.6.
cmake_policy (VERSION 2.6)

project (LibEmoTests)


find_package (LibEmo REQUIRED)
find_package (CppUnit REQUIRED)

#
# Test list.
#

# This file contains description of all tests.
include (LibEmoTests.cmake)

foreach (EMO_TEST_NAMES_ITER ${EMO_TEST_NAMES})
    include (${EMO_TEST_NAMES_ITER}.cmake OPTIONAL)
endforeach ()

include_directories(SYSTEM ${LIBEMO_INCLUDE_DIR})
include_directories(SYSTEM ${CPPUNIT_INCLUDE_DIR})

add_executable (${PROJECT_NAME}
       tests.cpp
       ${EMO_TEST_CLASSES}
)
add_library (${PROJECT_NAME}
       ${CPPUNIT_LIBRARY}
)
add_dependencies (${PROJECT_NAME} Emo)
