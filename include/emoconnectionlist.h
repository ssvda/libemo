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

#ifndef __EMO_CONNECTIONLISTHEAD_H
#define __EMO_CONNECTIONLISTHEAD_H

#include <emodefs.h>
#include <emotypes.h>
#include <emoconnectionlistnode.h>
#include <emoconnectionlistnodebase.h>
#include <emoconnectionlistengine.h>

EMO_BEGIN_NAMESPACE

template <EmoSizeType NumberOfItems,
          EmoSizeType ItemsInExtend>
class EmoConnectionList
	:public EmoConnectionListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>
{
public:
	typedef typename EmoConnectionListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>::ListEngine ListEngine;
	typedef typename ListEngine::template Buffer<NumberOfItems> ListBuffer;
	typedef EmoConnectionList<NumberOfItems, ItemsInExtend> NodeType;
	typedef EmoConnectionListNode<ItemsInExtend> ExtendType;
	
	EmoConnectionList()
		:m_next(0)
	{
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	~EmoConnectionList()
	{
		this->reduce();
	}
	
private:
	inline
	void extend()
	{
		if(this->m_next == 0)
			this->m_next = emoAlloc<ExtendType>();
	}
	
	inline
	void reduce()
	{
		if(this->m_next != 0)
		{
			emoDelete(this->m_next);
			this->m_next = 0;
		}
	}
	
public:
	EmoConnection *connect(EmoConnection *source)
	{
		register EmoConnection *connection = this->doConnect(source, &this->m_buffer, NumberOfItems);
		if(connection == 0)
		{
			this->extend();
			register ExtendType *e;
			register ExtendType *n = this->m_next;
			do
			{
				e = n;
				connection = e->connect(source);
				n = e->next();
			}
			while(n != 0 && connection != 0);
			if(connection == 0)
			{
				e->extend();
				e->next()->connect(source);
			}
		}
		return connection;
	}
	
	void disconnect(EmoConnection *pattern)
	{
		this->doDisconnect(pattern, &this->m_buffer, NumberOfItems);
		if(this->m_next != 0)
		{
			register ExtendType *e = this->m_next;
			while(e != 0)
			{
				e->disconnect(pattern);
				e = e->next();
			}
		}
	}
	
	void call(void **arguments)
	{
		this->doCall(arguments, &this->m_buffer, NumberOfItems);
		if(this->m_next != 0)
		{
			register ExtendType *e = this->m_next;
			while(e != 0)
			{
				e->call(arguments);
				e = e->next();
			}
		}
	}
	
	inline
	void clear()
	{
		this->reduce();
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	
	inline
	void optimize()
	{
		// TODO Defragmetation of list.
	}
	
private:
	ExtendType *m_next;
	ListBuffer m_buffer;
};

EMO_END_NAMESPACE

#endif // __EMO_CONNECTIONLISTHEAD_H

