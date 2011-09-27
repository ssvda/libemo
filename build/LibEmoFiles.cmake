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
	emoobjectbase.h
	emoobject.h
	emobind.h
	emoslotmastertype.h
	emoslot.h
	emobindinglist.h
	emobindinglistnodebase.h
	emobindinglistnode.h
	emosigned.h
	emoslotbase.h
	emofxs.h
	emotypifiedif.h
	emobestfitint.h
	emobindinglistengine.h
	emobinding.h
	emodefs.h
	emotypes.h
	emomemory.h
	emometacontainer.h
	emosignal.h
	emosignalinternals.h
)

# General list of all Qt-style headers.
set (EMO_QTSTYLE_HEADERS_LIST
	EmoObject
	EmoSlot
	EmoSignal
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
set (EMO_SOURCES_DOX_LIST
	emoobjectbase.dox
	emoobject.dox
	emobind.dox
	emoslotmastertype.dox
	emoslot.dox
	emobindinglist.dox
	emobindinglistnodebase.dox
	emobindinglistnode.dox
	emosigned.dox
	emoslotbase.dox
	emofxs.dox
	emotypifiedif.dox
	emobestfitint.dox
	emobindinglistengine.dox
	emobinding.dox
	emodefs.dox
	emotypes.dox
	emomemory.dox
	emometacontainer.dox
	emosignal.dox
	emosignalinternals.dox
)

# Doxygen general documentation for whole library.
set (EMO_GENERAL_DOX_LIST
	intro.dox
	codecovenants.dox
)
