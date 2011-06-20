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
# Header files lists.
#

# General list of all c-style headers.
set (EMO_CSTYLE_HEADERS_LIST
       emodefs.h
       emotypes.h
       emomemory.h
       emometacontainer.h
       emosignalbase.h
       emosignal.h
       emosignalinternals.h
)

# General list of all Qt-style headers.
set (EMO_QTSTYLE_HEADERS_LIST
       EmoSignal
)

# General list of all headers.
set (EMO_HEADERS_LIST
       ${EMO_CSTYLE_HEADERS_LIST}
       ${EMO_QTSTYLE_HEADERS_LIST}
)

#
# Source files list.
#

# General library sources.
set (EMO_SOURCES_LIST
       emosignalbase.cpp
)

#
# Documentation.
#

# Doxygen documentation for sources.
set (EMO_SOURCES_DOCUMENTATION_LIST
       emodefs.dox
       emotypes.dox
       emomemory.dox
       emometacontainer.dox
       emosignalbase.dox
       emosignal.dox
       emosignalinternals.dox
)

# Doxygen general documentation for whole library.
set (EMO_GENERAL_DOCUMENTATION_LIST
       intro.dox
)

# All Doxygen documentation.
set (EMO_DOXYGEN_DOCUMENTATION_LIST
       ${EMO_SOURCES_DOCUMENTATION_LIST}
       ${EMO_GENERAL_DOCUMENTATION_LIST}
)

#
# Make-systems specifications and packets for LibEmo.
#

# CMake find-package for LibEmo.
set (EMO_CMAKE_FIND_DIR ${CMAKE_SOURCE_DIR}/mkspec/cmake-2.6/Modules)
set (EMO_CMAKE_FIND ${EMO_CMAKE_FIND_DIR}/FindLibEmo.cmake)

#
# Lists processing.
#

foreach(FILE ${EMO_HEADERS_LIST})
  list(APPEND EMO_HEADERS ${CMAKE_SOURCE_DIR}/include/${FILE})
endforeach()

foreach(FILE ${EMO_SOURCES_LIST})
  list(APPEND EMO_SOURCES ${CMAKE_SOURCE_DIR}/libemo/${FILE})
endforeach()

foreach(FILE ${EMO_DOXYGEN_DOCUMENTATION_LIST})
  list(APPEND EMO_DOXYGEN_DOCUMENTATION ${CMAKE_SOURCE_DIR}/doc/${FILE})
endforeach()
