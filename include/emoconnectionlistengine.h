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

#ifndef __EMO_CONNECTIONLISTENGINE_H
#define __EMO_CONNECTIONLISTENGINE_H

#include <emodefs.h>
#include <emotypes.h>
#include <emoconnection.h>
#include <emobestfitint.h>
#include <emotypifiedif.h>
#include <emofxs.h>
#include <emomemory.h>

EMO_BEGIN_NAMESPACE

template <EmoBool IsItWiderThanBus>
class EmoConnectionListEngine
{
};

template <>
class EmoConnectionListEngine<false>
{
private:
#if defined(EMO_64BIT)
	typedef EMO_TYPIFIED_IF(sizeof(EmoULong) > sizeof(EmoUInt), EmoULong, EmoUInt) BitFieldType;
#else // defined(EMO_64BIT)
	typedef EmoUInt BitFieldType;
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
		EmoConnection m_list[NumberOfItems];
	};
	
	typedef Buffer<32> Buffer32;

	static
	void initialize(BufferBase *connectionList,
	                EmoSizeType listSize)
	{
		// Set field to initial state.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(connectionList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(connectionList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
		else if(listSize <= 32)
			static_cast<Buffer32*>(connectionList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
#if defined(EMO_64BIT)
		else if(listSize <= 64)
			static_cast<Buffer<64> *>(connectionList)->m_state = ~BitFieldType(0) >> EMO_BITS_IN_TYPE(BitFieldType) - listSize;
#endif // defined(EMO_64BIT)
	}
	
	static
	EmoConnection *allocate(BufferBase *connectionList,
	                        EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoConnection *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		// Free cells is absent.
		if(f == 0)
			return 0;
		
		register EmoInt i = emoFls(f);
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Clear corresponding bit.
		f &= ~(1 << i);
		
		// Save values.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(connectionList)->m_state = f;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(connectionList)->m_state = f;
		else if(listSize <= 32)
			static_cast<Buffer<32> *>(connectionList)->m_state = f;
#if defined(EMO_64BIT)
		if(listSize <= 64)
			static_cast<Buffer<64> *>(connectionList)->m_state = f;
#endif // defined(EMO_64BIT)
		
		// Thats all.
		return b + i;
	}
	
	static
	void free(BufferBase *connectionList,
	          EmoConnection *current,
	          EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoConnection *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
		}
#endif // defined(EMO_64BIT)
		
		register EmoInt i = current - b;
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Set corresponding bit.
		f |= (1 << i);
		
		// Save values.
		if(listSize <= 8)
			static_cast<Buffer<8> *>(connectionList)->m_state = f;
		else if(listSize <= 16)
			static_cast<Buffer<16> *>(connectionList)->m_state = f;
		else if(listSize <= 32)
			static_cast<Buffer<32> *>(connectionList)->m_state = f;
#if defined(EMO_64BIT)
		if(listSize <= 64)
			static_cast<Buffer<64> *>(connectionList)->m_state = f;
#endif // defined(EMO_64BIT)
		
		// NOTE We don't need to clear the field of the slot. It's just a good form.
		(b + i)->m_slot = 0;
	}
	
	static
	EmoConnection *iterate(BufferBase *connectionList,
	                       EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoConnection *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
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
	EmoConnection *next(BufferBase *connectionList,
	                    EmoConnection *current,
	                    EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoConnection *b;
		
		// Load values.
		if(listSize <= 8)
		{
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
		}
		else if(listSize <= 16)
		{
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
		}
		else if(listSize <= 32)
		{
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
		}
#if defined(EMO_64BIT)
		else if(listSize <= 64)
		{
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
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
	
private:
	EmoConnectionListEngine();
};

template <>
class EmoConnectionListEngine<true>
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
		EmoConnection m_list[NumberOfItems];
	};
	
	static
	void initialize(BufferBase *connectionList,
	                EmoSizeType listSize)
	{
		emoMemSet(connectionList, 0, (listSize - 1) * sizeof(EmoConnection) + sizeof(Buffer<1>));
	}
	
	static
	EmoConnection *allocate(BufferBase *connectionList,
	                        EmoSizeType listSize)
	{
		register EmoConnection *current = static_cast<Buffer<1> *>(connectionList)->m_list;
		for(register EmoInt i = 0; i < listSize; ++i, ++current)
			if(current->m_slot == 0)
				return current;
		return 0;
	}
	
	static
	void free(BufferBase *connectionList,
	          EmoConnection *current,
	          EmoSizeType listSize)
	{
		current->m_slot = 0;
	}
	
	static
	EmoConnection *iterate(BufferBase *connectionList,
	                       EmoSizeType listSize)
	{
		register EmoConnection *current = static_cast<Buffer<1> *>(connectionList)->m_list;
		for(register EmoInt i = 0; i < listSize; ++i, ++current)
			if(current->m_slot != 0)
				return current;
		return 0;
	}
	
	static
	EmoConnection *next(BufferBase *connectionList,
	                    EmoConnection *current,
	                    EmoSizeType listSize)
	{
		register EmoInt i = current - static_cast<Buffer<1> *>(connectionList)->m_list;
		while(++i < listSize)
		{
			if((++current)->m_slot != 0)
				return current;
		}
		return 0;
	}
	
private:
	EmoConnectionListEngine();
};

EMO_END_NAMESPACE

#endif // __EMO_CONNECTIONLISTENGINE_H

