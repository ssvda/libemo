/*
	Embeded Meta Objects (EMO) Library
	
	Copyright (C) 2011  Dmitry A. Sysoev
	Copyright (C) 2011  Yuri O. Nuzhdin
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __EMO_SLOT_H
#define __EMO_SLOT_H

#include <emodefs.h>
#include <emoslotmastertype.h>

EMO_BEGIN_NAMESPACE

template <typename SlotMasterType,
          typename MemberFunction>
class EmoSlot
{
private:
	EmoSlot();
};

#define EMO_SLOT(SLOTNAME) \
		EMO_SLOT_MASTER_TYPE(SLOTNAME), void (EMO_SLOT_MASTER_TYPE(SLOTNAME)::*)

#if defined(EMO_DO_NOT_EXPORT_WITHOUT_PREFIX)
#	define SLOT(SLOTNAME) EMO_SLOT(SLOTNAME)
#endif // defined(EMO_DO_NOT_EXPORT_WITHOUT_PREFIX)

EMO_END_NAMESPACE

#endif // __EMO_SLOT_H

