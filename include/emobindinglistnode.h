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

#ifndef __EMO_BINDINGLISTNODE_H
#define __EMO_BINDINGLISTNODE_H

#include <emodefs.h>
#include <emotypes.h>
#include <emobindinglistengine.h>
#include <emobinding.h>
#include <emobindinglistnodebase.h>

EMO_BEGIN_NAMESPACE

template <EmoSizeType NumberOfItems>
class EmoBindingListNode
	:public EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>
{
public:
	typedef typename EmoBindingListNodeBase<(NumberOfItems > EMO_BUS_WIDTH)>::ListEngine ListEngine;
	typedef typename ListEngine::template Buffer<NumberOfItems> ListBuffer;
	typedef EmoBindingListNode<NumberOfItems> NodeType;
	
	EmoBindingListNode()
		:m_next(0)
	{
		ListEngine::initialize(&this->m_buffer, NumberOfItems);
	}
	~EmoBindingListNode()
	{
		this->reduce();
	}
	
	inline
	void extend()
	{
		if(this->m_next == 0)
			this->m_next = emoAlloc<NodeType>();
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
	
	inline
	NodeType *next()
	{
		return this->m_next;
	}
	
	inline
	ListBuffer *buffer()
	{
		return &this->m_buffer;
	}
	
	inline
	EmoBinding *bind(EmoBinding *source)
	{
		return this->doBind(source, &this->m_buffer, NumberOfItems);
	}
	
	inline
	void unbind(EmoBinding *pattern)
	{
		this->doUnbind(pattern, &this->m_buffer, NumberOfItems);
	}
	
	inline
	void call(void **arguments)
	{
		this->doCall(arguments, &this->m_buffer, NumberOfItems);
	}
	
	inline
	EmoBool empty()
	{
		return ListEngine::empty(&this->m_buffer, NumberOfItems);
	}
	
private:
	NodeType *m_next;
	ListBuffer m_buffer;
};

EMO_END_NAMESPACE

#endif // __EMO_BINDINGLISTNODE_H

