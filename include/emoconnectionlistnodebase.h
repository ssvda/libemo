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

#ifndef __EMO_CONNECTIONLISTNODEBASE_H
#define __EMO_CONNECTIONLISTNODEBASE_H

#include <emodefs.h>
#include <emotypes.h>
#include <emoconnection.h>
#include <emoconnectionlistengine.h>

EMO_BEGIN_NAMESPACE

template <EmoBool IsItWiderThanBus>
class EmoConnectionListNodeBase
{
public:
	typedef EmoConnectionListEngine<IsItWiderThanBus> ListEngine;
	typedef ListEngine::BufferBase BufferBase;
	
protected:
	EmoConnection *doConnect(EmoConnection *source,
	                         BufferBase *buffer,
	                         EmoSizeType numberOfItems)
	{
		register EmoConnection *connection = ListEngine::allocate(buffer, numberOfItems);
		if(connection != 0)
		{
			connection->m_object = source->m_object;
			connection->m_slot = source->m_slot;
		}
		return connection;
	}
	
	void doDisconnect(EmoConnection *pattern,
	                  BufferBase *buffer,
	                  EmoSizeType numberOfItems)
	{
		register EmoConnection *connection = ListEngine::iterate(buffer, numberOfItems);
		if(pattern->m_object != 0)
		{
			while(connection != 0)
			{
				if(connection->m_object == pattern->m_object && connection->m_slot == pattern->m_slot)
				{
					ListEngine::free(connection, buffer, numberOfItems);
					connection = ListEngine::next(connection, buffer, numberOfItems);
				}
			}
		}
		else
		{
			while(connection != 0)
			{
				if(connection->m_slot == pattern->m_slot)
				{
					ListEngine::free(connection, buffer, numberOfItems);
					connection = ListEngine::next(connection, buffer, numberOfItems);
				}
			}
		}
	}
	
	void doCall(void **arguments,
	            BufferBase *buffer,
	            EmoSizeType numberOfItems)
	{
		register EmoConnection *connection = ListEngine::iterate(buffer, numberOfItems);
		while(connection != 0)
		{
			if(connection->m_object == pattern->m_object && connection->m_slot == pattern->m_slot)
			{
				// TODO connection->m_slot->call(arguments);
				connection = ListEngine::next(connection, buffer, numberOfItems);
			}
		}
	}
};

EMO_END_NAMESPACE

#endif // __EMO_CONNECTIONLISTNODEBASE_H

