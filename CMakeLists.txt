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
# General settings.

# Minimal required version of CMake.
cmake_minimum_required(VERSION 2.6)

# Whole project name
project(libemo)

# Version of the LibEmo.
set(EMO_VERSION 1)

################################################################################
# Options.

option(
  __EMO_SLOT_STATIC_DEF
  "Allocate slots staticly (for some dull compilers)" OFF
)

# Configure file defenitions
# configure_file(
#   "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#   "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#   )
#add_executable(Tutorial tutorial.cxx)

################################################################################
# General project structure.



# Source code of LibEmo library.
add_subdirectory(libemo)

