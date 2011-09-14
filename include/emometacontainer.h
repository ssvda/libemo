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

#ifndef __EMO_METACONTAINER_H
#define __EMO_METACONTAINER_H

#include <emodefs.h>
#include <emotypes.h>
#include <emomemory.h>

EMO_BEGIN_NAMESPACE

enum EmoAllocationType
{
	StaticalAllocation,
	DynamicalAllocation,
	SharedAllocation
};

template <typename ValueType,
          EmoAllocationType =  DynamicalAllocation>
class EmoMetaContainer
{
private:
	EmoMetaContainer();
};

template <typename ValueType>
class EmoMetaContainer<ValueType, StaticalAllocation>
{
public:
	typedef ValueType ElementType;
	enum
	{
		AllocationMethod = StaticalAllocation
	};
	
	inline
	EmoMetaContainer()
		:m_element()
	{}
	
	inline
	void allocate()
	{}
	inline
	void free()
	{}
	inline
	bool allocated()
	{
		return true;
	}
	inline
	ElementType &element()
	{
		return this->m_element;
	}
	
private:
	ElementType m_element;
};

template <typename ValueType>
class EmoMetaContainer<ValueType, DynamicalAllocation>
{
public:
	typedef ValueType ElementType;
	enum
	{
		AllocationMethod = DynamicalAllocation
	};
	
	inline
	~EmoMetaContainer()
	{
		this->free();
	}
	
	inline
	void allocate()
	{
		if(this->m_element == 0)
			this->m_element = emoAlloc<ElementType>;
	}
	inline
	void free()
	{
		if(this->m_element != 0)
		{
			emoDelete(this->m_element);
			this->m_element = 0;
		}
	}
	inline
	bool allocated()
	{
		return this->m_element != 0;
	}
	inline
	ElementType &element()
	{
		if(this->m_element == 0)
			this->allocate();
		return *this->m_element;
	}
	
private:
	ElementType *m_element;
};

template <typename ValueType>
class EmoMetaContainer<ValueType, SharedAllocation>
{
public:
	typedef ValueType ElementType;
	enum
	{
		AllocationMethod = SharedAllocation
	};
	
	inline
	EmoMetaContainer()
		:m_element()
	{}
	
	inline
	void allocate()
	{}
	inline
	void free()
	{}
	inline
	bool allocated()
	{
		return true;
	}
	inline
	ElementType &element()
	{
		return this->m_element;
	}
	
private:
	static
	ElementType m_element;
};

EMO_END_NAMESPACE

#endif // __EMO_METACONTAINER_H
