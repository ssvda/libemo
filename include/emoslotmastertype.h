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

#ifndef __EMO_SLOTMASTERTYPE_H
#define __EMO_SLOTMASTERTYPE_H

#include <emodefs.h>

EMO_BEGIN_NAMESPACE

EMO_BEGIN_INTERNAL_NAMESPACE

struct EmoSlotBinding
{
};

typedef void (*EmoSlotBindingFunction)(EmoSlotBinding);

EMO_END_INTERNAL_NAMESPACE

template <Intern::EmoSlotBindingFunction Binding>
class EmoSlotMasterType
{
private:
	EmoSlotMasterType();
};

#define EMO_SLOT_MASTER_TYPE(SLOTNAME) \
		Emo::EmoSlotMasterType<&SLOTNAME>::MasterType

#define EMO_REGISTER_SLOT_MASTER_TYPE(SLOTNAME,MASTER) \
		EMO_BEGIN_NAMESPACE \
		template <> \
		class EmoSlotMasterType<&SLOTNAME> \
		{ \
		public: \
			typedef MASTER MasterType; \
		}; \
		EMO_END_NAMESPACE

#define EMO_SLOT_MASTER_TYPE_BINDING(SLOTNAME) \
		static \
		void SLOTNAME(Emo::Intern::EmoSlotBinding);

EMO_END_NAMESPACE

#endif // __EMO_SLOTMASTERTYPE_H

