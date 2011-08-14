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
	typedef EMO_TYPIFIED_IF(sizeof(EmoLong) > sizeof(EmoInt), EmoLong, EmoInt) BitFieldType;
#else // defined(EMO_64BIT)
	typedef EmoInt BitFieldType;
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
		typedef EMO_BEST_FIT_INT(NumberOfItems) StateType;
		StateType m_state;
		EmoConnection m_list[NumberOfItems];
	};
	
	static
	EmoConnection *allocate(BufferBase *connectionList,
	                        EmoSizeType listSize)
	{
		register BitFieldType f;
		EmoConnection *b;
		
		// Load values.
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
			break;
		case 16:
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
			break;
		case 8:
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
			break;
		}
		
		// Free cells is absent.
		if(f == 0)
			return 0;
		
		register EmoInt i = EmoFls(f);
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Clear corresponding bit.
		f &= ~(1 << (listSize - i));
		
		// Save values.
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			static_cast<Buffer<64> *>(connectionList)->m_state = f;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			static_cast<Buffer<32> *>(connectionList)->m_state = f;
			break;
		case 16:
			static_cast<Buffer<16> *>(connectionList)->m_state = f;
			break;
		case 8:
			static_cast<Buffer<8> *>(connectionList)->m_state = f;
			break;
		}
		
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
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
			break;
		case 16:
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
			break;
		case 8:
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
			break;
		}
		
		register EmoInt i = current - b;
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Set corresponding bit.
		f |= (listSize - i);
		
		// Save values.
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			static_cast<Buffer<64> *>(connectionList)->m_state = f;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			static_cast<Buffer<32> *>(connectionList)->m_state = f;
			break;
		case 16:
			static_cast<Buffer<16> *>(connectionList)->m_state = f;
			break;
		case 8:
			static_cast<Buffer<8> *>(connectionList)->m_state = f;
			break;
		}
		
		// NOTE We don't need to clear the field of the slot. It's just a good form.
		(b + i)->m_slot = 0;
	}
	
	static
	EmoConnection *iterate(BufferBase *connectionList,
	                       EmoSizeType listSize)
	{
		register BitFieldType f;
		register BitFieldType mask;
		EmoConnection *b;
		
		// Load values.
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			mask = ~static_cast<Buffer<64>::StateType>(0);
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			mask = ~static_cast<Buffer<32>::StateType>(0);
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
			break;
		case 16:
			mask = ~static_cast<Buffer<16>::StateType>(0);
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
			break;
		case 8:
			mask = ~static_cast<Buffer<8>::StateType>(0);
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
			break;
		}
		
		// Find first allocated cell.
		register EmoInt i = EmoFls((~f) & mask);
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
		register BitFieldType mask;
		EmoConnection *b;
		
		// Load values.
		switch(listSize)
		{
#if defined(EMO_64BIT)
		case 64:
			mask = ~static_cast<Buffer<64>::StateType>(0);
			f = static_cast<Buffer<64> *>(connectionList)->m_state;
			b = static_cast<Buffer<64> *>(connectionList)->m_list;
			break;
#endif // defined(EMO_64BIT)
		case 32:
			mask = ~static_cast<Buffer<32>::StateType>(0);
			f = static_cast<Buffer<32> *>(connectionList)->m_state;
			b = static_cast<Buffer<32> *>(connectionList)->m_list;
			break;
		case 16:
			mask = ~static_cast<Buffer<16>::StateType>(0);
			f = static_cast<Buffer<16> *>(connectionList)->m_state;
			b = static_cast<Buffer<16> *>(connectionList)->m_list;
			break;
		case 8:
			mask = ~static_cast<Buffer<8>::StateType>(0);
			f = static_cast<Buffer<8> *>(connectionList)->m_state;
			b = static_cast<Buffer<8> *>(connectionList)->m_list;
			break;
		}
		
		// Calculate current cell.
		register EmoInt i = current - b;
		EMO_ASSERT(i >= 0 && i < listSize);
		
		// Is it end?
		if(i == listSize - 1)
			return 0;
		
		// Applay mask to disable previous cells.
		f &= mask >> (i + 1);
		
		// Find next allocated cell.
		i = EmoFls(f);
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
	EmoConnection *allocate(BufferBase *connectionList,
	                        EmoSizeType listSize)
	{
		register EmoConnection *current = connectionList->m_list;
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
		register EmoConnection *current = connectionList->m_list;
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
		register EmoInt i = current - connectionList->m_list;
		while(++i < listSize)
		{
			if(++current->m_slot != 0)
				return current;
		}
		return 0;
	}
	
private:
	EmoConnectionListEngine();
};

EMO_END_NAMESPACE

#endif // __EMO_CONNECTIONLISTENGINE_H

