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
# Configuring a project variables

set(EMO_FORCE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

################################################################################
# Including a general instructions

include("${PROJECT_SOURCE_DIR}/mkspec/cmake/LibEmo.cmake")

################################################################################
# List of sources files
set(EMO_SOURCES_FILES
  "${PROJECT_SOURCE_DIR}/libemo/main.cpp"
)

################################################################################
# Adding a library
add_library(LibEmo ${EMO_SOURCES_FILES} ${EMO_HEADERS_FILES})