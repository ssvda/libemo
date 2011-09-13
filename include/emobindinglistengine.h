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

#ifndef __EMO_BINDINGLISTENGINE_H
#define __EMO_BINDINGLISTENGINE_H

#include <emodefs.h>
#include <emotypes.h>
#include <emobinding.h>
#include <emobestfitint.h>
#include <emotypifiedif.h>
#include <emofxs.h>
#include <emomemory.h>

EMO_BEGIN_NAMESPACE

template <EmoBool IsItWiderThanBus>
class EmoBindingListEngine
{
};

template <>
class EmoBindingListEngine<false>
{
private:
#if defined(EMO_64BIT)
	typedef EMO_BEST_FIT_INT(64) BitFieldType;
#else // defined(EMO_64BIT)
	typedef EMO_BEST_FIT_INT(32) BitFieldType;
#endif // defined(EMO_64BIT)
	
public:
	class BufferBase
	{
	};
	
	template <EmoSizeType NumberOfItems>
	class Buffer
		: public BufferBase
	{
	public:
		typedef typename EMO_BEST_FIT_INT(NumberOfItems) StateType;
		StateType m_state;
		EmoBinding m_list[NumberOfItems];
	};

	static
	void initialize(BufferBase *bindingList,
	                EmoSizeType listSize)
	{
		// Set field to initial state.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(bindingList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(bindingList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
		else if(listSize <= 32)
			static_cast<Buffer<32> *>(bindingList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
#if defined(EMO_64BIT)
		else if(listSize <= 64)
			static_cast<Buffer<64> *>(bindingList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
#endif // defined(EMO_64BIT)
	}
	
	static
	EmoBinding *allocate(BufferBase *bindingList,
	                        EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoBinding *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(bindingList)->m_state;
			b = static_cast<Buffer<8> *>(bindingList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(bindingList)->m_state;
			b = static_cast<Buffer<16> *>(bindingList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(bindingList)->m_state;
			b = static_cast<Buffer<32> *>(bindingList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(bindingList)->m_state;
			b = static_cast<Buffer<64> *>(bindingList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		// Free cells is absent.
		if(f == 0)
			return 0;
		
		register EmoInt i = emoFls(f);
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Clear corresponding bit.
		f &= ~(BitFieldType(1) << i);
		
		// Save values.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(bindingList)->m_state = f;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(bindingList)->m_state = f;
		else if(listSize <= 32)
			static_cast<Buffer<32> *>(bindingList)->m_state = f;
#if defined(EMO_64BIT)
		if(listSize <= 64)
			static_cast<Buffer<64> *>(bindingList)->m_state = f;
#endif // defined(EMO_64BIT)
		
		// Thats all.
		return b + i;
	}
	
	static
	void free(BufferBase *bindingList,
	          EmoBinding *current,
	          EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoBinding *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(bindingList)->m_state;
			b = static_cast<Buffer<8> *>(bindingList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(bindingList)->m_state;
			b = static_cast<Buffer<16> *>(bindingList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(bindingList)->m_state;
			b = static_cast<Buffer<32> *>(bindingList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(bindingList)->m_state;
			b = static_cast<Buffer<64> *>(bindingList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		register EmoInt i = current - b;
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Set corresponding bit.
		f |= (1 << i);
		
		// Save values.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(bindingList)->m_state = f;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(bindingList)->m_state = f;
		else if(listSize <= 32)
			static_cast<Buffer<32> *>(bindingList)->m_state = f;
#if defined(EMO_64BIT)
		if(listSize <= 64)
			static_cast<Buffer<64> *>(bindingList)->m_state = f;
#endif // defined(EMO_64BIT)
		
		// NOTE We don't need to clear the field of the slot. It's just a good form.
		(b + i)->m_slot = 0;
	}
	
	static
	EmoBinding *iterate(BufferBase *bindingList,
	                       EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoBinding *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(bindingList)->m_state;
			b = static_cast<Buffer<8> *>(bindingList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(bindingList)->m_state;
			b = static_cast<Buffer<16> *>(bindingList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(bindingList)->m_state;
			b = static_cast<Buffer<32> *>(bindingList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(bindingList)->m_state;
			b = static_cast<Buffer<64> *>(bindingList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		BitFieldType mask = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
		
		// Find first allocated cell.
		register EmoInt i = emoFls((~f) & mask);
		EMO_ASSERT(i >= -1 && i < listSize);
		
		if(i == -1)
			return 0;
		
		return b + i;
	}
	
	static
	EmoBinding *next(BufferBase *bindingList,
	                    EmoBinding *current,
	                    EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoBinding *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(bindingList)->m_state;
			b = static_cast<Buffer<8> *>(bindingList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(bindingList)->m_state;
			b = static_cast<Buffer<16> *>(bindingList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(bindingList)->m_state;
			b = static_cast<Buffer<32> *>(bindingList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(bindingList)->m_state;
			b = static_cast<Buffer<64> *>(bindingList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		// Calculate current cell.
		register EmoInt i = current - b;
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Is it end?
		if(i == 0)
			return 0;
		
		BitFieldType mask = ~(~static_cast<BitFieldType>(0) << i);
		
		// Find next allocated cell.
		i = emoFls((~f) & mask);
		EMO_ASSERT(i >= -1 && i < listSize);
		
		if(i == -1)
			return 0;
		
		return b + i;
	}
	
	static
	EmoBool empty(BufferBase *bindingList,
	              EmoSizeType listSize)
	{
		register BitFieldType f;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(bindingList)->m_state;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(bindingList)->m_state;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(bindingList)->m_state;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(bindingList)->m_state;
		}
#endif // defined(EMO_64BIT)
		
		// Test for equality to mask.
		return f == ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
	}
	
private:
	EmoBindingListEngine();
};

template <>
class EmoBindingListEngine<true>
{
public:
	class BufferBase
	{
	};
	
	template <EmoSizeType NumberOfItems>
	class Buffer
		: public BufferBase
	{
	public:
		EmoBinding m_list[NumberOfItems];
	};
	
	static
	void initialize(BufferBase *bindingList,
	                EmoSizeType listSize)
	{
		emoMemSet(bindingList, 0, (listSize - 1) * sizeof(EmoBinding) + sizeof(Buffer<1>));
	}
	
	static
	EmoBinding *allocate(BufferBase *bindingList,
	                        EmoSizeType listSize)
	{
		register EmoBinding *current = static_cast<Buffer<1> *>(bindingList)->m_list;
		for(register EmoInt i = 0; i < listSize; ++i, ++current)
			if(current->m_slot == 0)
				return current;
		return 0;
	}
	
	static
	void free(BufferBase *bindingList,
	          EmoBinding *current,
	          EmoSizeType listSize)
	{
		current->m_slot = 0;
	}
	
	static
	EmoBinding *iterate(BufferBase *bindingList,
	                       EmoSizeType listSize)
	{
		register EmoBinding *current = static_cast<Buffer<1> *>(bindingList)->m_list;
		for(register EmoInt i = 0; i < listSize; ++i, ++current)
			if(current->m_slot != 0)
				return current;
		return 0;
	}
	
	static
	EmoBinding *next(BufferBase *bindingList,
	                    EmoBinding *current,
	                    EmoSizeType listSize)
	{
		register EmoInt i = current - static_cast<Buffer<1> *>(bindingList)->m_list;
		while(++i < listSize)
		{
			if((++current)->m_slot != 0)
				return current;
		}
		return 0;
	}
	
	static inline
	EmoBool empty(BufferBase *bindingList,
	              EmoSizeType listSize)
	{
		return iterate(bindingList, listSize) == 0;
	}
	
private:
	EmoBindingListEngine();
};

EMO_END_NAMESPACE

#endif // __EMO_BINDINGLISTENGINE_H

