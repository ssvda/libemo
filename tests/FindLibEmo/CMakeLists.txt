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

project (FindLibEmo)

#
# Adding LibEmo.
#

find_package (LibEmo REQUIRED)

#
# Defenitions.
#

add_executable (${PROJECT_NAME}
       main.cpp
)

target_link_libraries (${PROJECT_NAME}
    Emo
)

build_after_libemo (${PROJECT_NAME})
