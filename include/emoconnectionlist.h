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

#ifndef __EMO_CONECTIONLIST_H
#define __EMO_CONECTIONLIST_H

#include <emodefs.h>
#include <emotypes.h>
#include <emomemory.h>
#include <emometacontainer.h>

EMO_BEGIN_NAMESPACE

// Forward declarations
class EmoObject;
class EmoSlotBase;

struct EmoConnection
{
	EmoObject *m_object;
	EmoSlotBase *m_slot;
};

template <EmoAllocationType p_AllocationType,
          unsigned int p_FirstPortion,
          unsigned int p_ExtendPortion>
class EmoConnectionListBase
{
public:
	enum
	{
		AllocationType = p_AllocationType,
		FirstPortion = p_FirstPortion,
		ExtendPortion = p_ExtendPortion
	};
	
protected:
	typedef unsigned int ListStateType;
	
	struct ListExtend
	{
		Connection m_list[ExtendPortion];
		ListExtend *m_next;
	};
	
	struct ListHead
	{
		ListStateType m_state;
		Connection m_list[FirstPortion];
		ListExtend *m_next;
	};
	
	typedef ListExtend *IterationState;
	
	Connection *allocate();
	void free(Connection *connection);
	Connection *iterate(IterationState *state);
	
public:
	void clear();
	void unbind(EmoObject *object);
};

EMO_END_NAMESPACE

#endif // __EMO_CONECTIONLIST_H
