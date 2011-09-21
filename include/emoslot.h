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

#define EMO_SLOT_DECL(SLOTNAME, SIGNATURE, ARGUMENTS) \
		EMO_BEGIN_NAMESPACE \
		template <> \
		class EmoSlot<EMO_SLOT(SLOTNAME)SIGNATURE> \
			:public EmoSlotBase \
		{ \
		public: \
			typedef EmoSlot<EMO_SLOT(SLOTNAME)SIGNATURE> SlotType; \
			typedef EMO_SLOT_MASTER_TYPE(SLOTNAME) MasterType; \
			typedef void (*Signature)SIGNATURE; \
			static \
			SlotType *instance() \
			{ \
				static SlotType slot; \
				return &slot; \
			} \
			void call(EmoObject *o, void **a) \
			{ \
				static_cast<MasterType *>(o)->SLOTNAME ARGUMENTS; \
			} \
		}; \
		EMO_END_NAMESPACE

#define EMO_SLOT_ARGUMENT(N, TYPE) \
		*static_cast< TYPE *>(a[N])

// Just some abbreviations:
#define EMO_SLOTS(SLOTNAME) \
		EMO_SLOT_MASTER_TYPE_BINDING(SLOTNAME)
#define EMO_MASTER(SLOTNAME, MASTERTYPE) \
		EMO_REGISTER_SLOT_MASTER_TYPE(SLOTNAME, MASTERTYPE)

EMO_END_NAMESPACE

#endif // __EMO_SLOT_H

