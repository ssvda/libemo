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
# LibEmo requiements.
#

#find_package(stdlibs REQUIRED)
#find_package(libstdc++ REQUIRED)

#
# Pkg-config bindings.
#

# Find Pkg-config module (quietly).
find_package(PkgConfig)
# Chaeck for a module.
pkg_check_modules(PC_LIBEMO QUIET libemo)

#
# LibEmo definitions.
#

set(LIBEMO_DEFINITIONS ${PC_LIBEMO_CFLAGS_OTHER})

#
# LibEmo includes.
#

find_path(LIBEMO_INCLUDE_DIR
       NAMES emodefs.h emotypes.h EmoSignal
       HINTS ${PC_LIBEMO_INCLUDEDIR} ${PC_LIBEMO_INCLUDE_DIRS}
       PATH_SUFFIXES Emo
       DOC "LibEmo includes path"
)

#
# LibEmo library.
#

find_library(LIBEMO_LIBRARY
       NAMES emo libEmo
       HINTS ${PC_LIBEMO_LIBDIR} ${PC_LIBEMO_LIBRARY_DIRS}
       DOC "LibEmo library"
)

#
# Standard packet processing.
#

# Setup default variables.
set (LIBEMO_LIBRARIES ${LIBEMO_LIBRARY})
set (LIBEMO_INCLUDE_DIRS ${LIBEMO_INCLUDE_DIR})

# Handle the QUIETLY and REQUIRED arguments and set LIBEMO_FOUND to TRUE
# if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibEmo
       DEFAULT_MSG
       LIBEMO_LIBRARY
       LIBEMO_INCLUDE_DIR
)



mark_as_advanced(LIBEMO_INCLUDE_DIR LIBEMO_LIBRARY)


