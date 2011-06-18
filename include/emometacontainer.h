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

template <typename ValueType,
          bool useDynamicAllocation>
class EmoMetaContainer
{
private:
	EmoMetaContainer();
};

template <typename ValueType>
class EmoMetaContainer<ValueType, false>
{
public:
	typedef ValueType ElementType;
	enum
	{
		DynamicAllocationAllowed = false
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
class EmoMetaContainer<ValueType, true>
{
public:
	typedef ValueType ElementType;
	enum
	{
		DynamicAllocationAllowed = true
	};
	
	inline
	void allocate()
	{
		if(this->m_element == 0)
			this->m_element = new(EmoNewOperator) ElementType();
	}
	inline
	void free()
	{
		if(this->m_element != 0)
		{
			delete(EmoNewOperator) this->m_element;
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
		return *this->m_element;
	}
	
private:
	ElementType *m_element;
};

EMO_END_NAMESPACE

#endif // __EMO_METACONTAINER_H
