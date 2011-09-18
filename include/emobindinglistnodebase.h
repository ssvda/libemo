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

#ifndef __EMO_BINDINGLISTNODEBASE_H
#define __EMO_BINDINGLISTNODEBASE_H

#include <emodefs.h>
#include <emotypes.h>
#include <emobinding.h>
#include <emobindinglistengine.h>
#include <emoslotbase.h>

EMO_BEGIN_NAMESPACE

template <EmoBool IsItWiderThanBus>
class EmoBindingListNodeBase
{
public:
	typedef EmoBindingListEngine<IsItWiderThanBus> ListEngine;
	typedef typename ListEngine::BufferBase BufferBase;
	
protected:
	EmoBinding *doBind(const EmoBinding *source,
	                   BufferBase *buffer,
	                   EmoSizeType numberOfItems)
	{
		register EmoBinding *binding = ListEngine::allocate(buffer, numberOfItems);
		if(binding != 0)
		{
			binding->m_object = source->m_object;
			binding->m_slot = source->m_slot;
		}
		return binding;
	}
	
	void doUnbind(const EmoBinding *pattern,
	              BufferBase *buffer,
	              EmoSizeType numberOfItems)
	{
		register EmoBinding *binding = ListEngine::iterate(buffer, numberOfItems);
		if(pattern->m_object != 0)
		{
			while(binding != 0)
			{
				if(binding->m_object == pattern->m_object && binding->m_slot == pattern->m_slot)
					ListEngine::free(buffer, binding, numberOfItems);
				binding = ListEngine::next(buffer, binding, numberOfItems);
			}
		}
		else
		{
			while(binding != 0)
			{
				if(binding->m_slot == pattern->m_slot)
					ListEngine::free(buffer, binding, numberOfItems);
				binding = ListEngine::next(buffer, binding, numberOfItems);
			}
		}
	}
	
	void doCall(void **arguments,
	            BufferBase *buffer,
	            EmoSizeType numberOfItems)
	{
		register EmoBinding *binding = ListEngine::iterate(buffer, numberOfItems);
		while(binding != 0)
		{
			binding->m_slot->call(binding->m_object, arguments);
			binding = ListEngine::next(buffer, binding, numberOfItems);
		}
	}
};

EMO_END_NAMESPACE

#endif // __EMO_BINDINGLISTNODEBASE_H

