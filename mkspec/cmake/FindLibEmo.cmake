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
# Check for forced hints.
#

if (DEFINED LIBEMO_FORCE_HINTS AND LIBEMO_FORCE_HINTS)
	
	# There are forced hints, so just assume it.
	
	# Is hints given?
	if (NOT DEFINED EMO_HINT_LIBRARY OR NOT DEFINED EMO_HINT_INCLUDEDIR)
		
		if (NOT LibEmo_FIND_QUIETLY)
			message (FATAL_ERROR "Hints EMO_HINT_LIBRARY and EMO_HINT_INCLUDEDIR must be defined in force-hints mode")
		endif (NOT LibEmo_FIND_QUIETLY)
		
	else (NOT DEFINED EMO_HINT_LIBRARY OR NOT DEFINED EMO_HINT_INCLUDEDIR)
		
		set (LIBEMO_INCLUDE_DIR "${EMO_HINT_INCLUDEDIR}")
		set (LIBEMO_LIBRARY "${EMO_HINT_LIBRARY}")
		
	endif (NOT DEFINED EMO_HINT_LIBRARY OR NOT DEFINED EMO_HINT_INCLUDEDIR)
	
else (DEFINED LIBEMO_FORCE_HINTS AND LIBEMO_FORCE_HINTS)
	
	# There are no forced hints. We must find library files.
	
	#
	# Pkg-config bindings.
	#
	
	# Find Pkg-config module (quietly).
	find_package(PkgConfig)
	# Check for a libemo module.
	pkg_check_modules(PC_LIBEMO QUIET libemo)
	
	#
	# Actually find LibEmo.
	#
	
	find_path (LIBEMO_INCLUDE_DIR
		NAMES emodefs.h emotypes.h EmoSignal
		HINTS ${EMO_HINT_INCLUDEDIR} ${PC_LIBEMO_INCLUDEDIR} ${PC_LIBEMO_INCLUDE_DIRS}
		DOC "LibEmo includes path"
	)
	
	find_library (LIBEMO_LIBRARY
		NAMES libEmo.a emo
		HINTS ${EMO_HINT_LIBRARY} ${PC_LIBEMO_LIBDIR} ${PC_LIBEMO_LIBRARY_DIRS}
		DOC "LibEmo library"
	)
	
endif (DEFINED LIBEMO_FORCE_HINTS AND LIBEMO_FORCE_HINTS)

#
# Handle standard arguments.
#

# Use standard package.
include (FindPackageHandleStandardArgs)
# Applay default procession.
find_package_handle_standard_args (LibEmo
	DEFAULT_MSG
	LIBEMO_LIBRARY
	LIBEMO_INCLUDE_DIR
)
# Place variables in cache.
mark_as_advanced (LIBEMO_LIBRARY)
mark_as_advanced (LIBEMO_INCLUDE_DIR)

#
# Configure compiler enveroment.
#

include_directories(SYSTEM ${LIBEMO_INCLUDE_DIR})
