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

# You may use this file to include LibEmo into you project.

if(DEFINED EMO_FORCE_INCLUDE_DIR)
  include_directories("${EMO_FORCE_INCLUDE_DIR}")
else()
  include_directories("${CMAKE_INCLUDE_PATH}/libemo")
endif()

set(EMO_HEADERS_FILES
  "${PROJECT_SOURCE_DIR}/include/emodefs.h"
  "${PROJECT_SOURCE_DIR}/include/emotypes.h"
  "${PROJECT_SOURCE_DIR}/include/emosignal.h"
)

