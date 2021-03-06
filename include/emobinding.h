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

#ifndef __EMO_BINDING_H
#define __EMO_BINDING_H

#include <emodefs.h>

EMO_BEGIN_NAMESPACE

// Forward declarations:
class EmoObjectBase;
class EmoSlotBase;

struct EmoBinding
{
	inline
	EmoBinding(EmoSlotBase *slot,
	           EmoObjectBase *object)
		:m_slot(slot),
		 m_object(object)
	{}
	inline
	EmoBinding()
	{}
	
	EmoSlotBase *m_slot;
	EmoObjectBase *m_object;
};

EMO_END_NAMESPACE

#endif // __EMO_BINDING_H

