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

#ifndef __EMO_BINDINGLISTHEAD_H
#define __EMO_BINDINGLISTHEAD_H

#include <emodefs.h>
#include <emotypes.h>
#include <emobindinglistnode.h>
#include <emobindinglistnodebase.h>
#include <emobindinglistengine.h>

EMO_BEGIN_NAMESPACE

template <EmoSizeType NumberOfItems,
          EmoSizeType ItemsInExtend>
class EmoBindingList
	:public EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>
{
public:
	typedef typename EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>::ListEngine ListEngine;
	typedef typename ListEngine::template Buffer<NumberOfItems> ListBuffer;
	typedef EmoBindingList<NumberOfItems, ItemsInExtend> NodeType;
	typedef EmoBindingListNode<ItemsInExtend> ExtendType;
	
	EmoBindingList()
		:m_next(0)
	{
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	~EmoBindingList()
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
	EmoBinding *bind(const EmoBinding *source)
	{
		register EmoBinding *binding = this->doBind(source, &this->m_buffer, NumberOfItems);
		if(binding == 0)
		{
			this->extend();
			register ExtendType *e;
			register ExtendType *n = this->m_next;
			do
			{
				e = n;
				binding = e->bind(source);
				n = e->next();
			}
			while(n != 0 && binding != 0);
			if(binding == 0)
			{
				e->extend();
				e->next()->bind(source);
			}
		}
		return binding;
	}
	
	void unbind(const EmoBinding *pattern)
	{
		this->doUnbind(pattern, &this->m_buffer, NumberOfItems);
		if(this->m_next != 0)
		{
			register ExtendType *e = this->m_next;
			while(e != 0)
			{
				e->unbind(pattern);
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

template <EmoSizeType NumberOfItems>
class EmoBindingList<NumberOfItems, 0>
	:public EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>
{
public:
	typedef typename EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>::ListEngine ListEngine;
	typedef typename ListEngine::template Buffer<NumberOfItems> ListBuffer;
	typedef EmoBindingList<NumberOfItems, 0> NodeType;
	
	EmoBindingList()
	{
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	
public:
	EmoBinding *bind(EmoBinding *source)
	{
		return this->doBind(source, &this->m_buffer, NumberOfItems);
	}
	
	void unbind(EmoBinding *pattern)
	{
		this->doUnbind(pattern, &this->m_buffer, NumberOfItems);
	}
	
	void call(void **arguments)
	{
		this->doCall(arguments, &this->m_buffer, NumberOfItems);
	}
	
	inline
	void clear()
	{
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	
	inline
	void optimize()
	{
	}
	
private:
	ListBuffer m_buffer;
};

EMO_END_NAMESPACE

#endif // __EMO_BINDINGLISTHEAD_H

