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
# LibEmo library.
#

add_library (Emo
       ${EMO_SOURCES}
       ${EMO_HEADERS}
       ${EMO_DOXYGEN_DOCUMENTATION}
)

#
# Prepare for tests.
#

file (WRITE "${CMAKE_SOURCE_DIR}/test/BuildHints.cmake" "set (EMO_SOURCE_DIR \"${CMAKE_SOURCE_DIR}\")\n")
file (APPEND "${CMAKE_SOURCE_DIR}/test/BuildHints.cmake" "set (EMO_BINARY_DIR \"${CMAKE_BINARY_DIR}\")\n")
