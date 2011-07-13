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

set (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
project (Emo)

#
# LibEmo version information.
#

set (LibEmo_MAJOR 0)
set (LibEmo_MINOR 0)

#
# LibEmo configuration.
#

# Use this file adjust configuration of you build of LibEmo.
# You can use LibEmoConfig.cmake.example file as template.
include (LibEmoConfig.cmake OPTIONAL)

#
# Project files list.
#

# This file contains list of all sources files in project.
include (LibEmoFiles.cmake)

#
# Project build rules.
#

# Adjust CMake to search find-package in local tree.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${EMO_CMAKE_FIND_DIR}")

# This file contains general build rules for project.
include (LibEmo.cmake)
