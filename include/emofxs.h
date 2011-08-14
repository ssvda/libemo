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

#ifndef __EMO_FXS_H
#define __EMO_FXS_H

#include <emodefs.h>
#include <emotypes.h>

EMO_BEGIN_NAMESPACE

EMO_BEGIN_INTERNAL_NAMESPACE

// This macroes used to reduse number of copy-paste operations.
// It's only suitable for use with this context and shouldn't
// be used in any other places.
#define EMO_GENERIC_FLS_ELEMENTARY_CELL(M, N) \
		if(!(t & (~((Integer)0) << (M - N)))) \
		{ \
			t <<= N; \
			b -= N; \
		}

template <typename IntegerType>
class EmoFxs
{
public:
	static inline
	IntegerType fls(const IntegerType v)
	{
		return ImplType::fls(v);
	}
	static inline
	IntegerType ffs(const IntegerType v)
	{
		return ImplType::ffs(v);
	}
	
private:
	template <typename Integer,
	          EmoInt NumberOfBits>
	struct Implementation
	{
	};
	
	typedef Implementation<IntegerType, EMO_BITS_IN_TYPE(IntegerType)> ImplType;
	
	
	
#if defined(EMO_64BIT)
	template <typename Integer>
	struct Implementation<Integer, 64>
	{
		static
		Integer genericFls(Integer v)
		{
			register EmoInt b = 64;
			register Integer t = v;
			
			if(!t)
				return -1;
			
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 32);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 16);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 8);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 4);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 2);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(64, 1);
			
			return b;
		}
		static inline
		Integer genericFfs(Integer v)
		{
			if(v == 0)
				return -1;
			return genericFls(v ^ (v - 1));
		}
		static inline
		Integer fls(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FLS64)
			return EMO_USE_CUSTOM_FLS64(v);
#else
			return genericFls(v);
#endif // defined(EMO_USE_CUSTOM_FLS64)
		}
		static inline
		Integer ffs(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FFS64)
			return EMO_USE_CUSTOM_FFS64(v);
#else
			return genericFfs(v);
#endif // defined(EMO_USE_CUSTOM_FLS64)
		}
	};
#endif // defined(EMO_64BIT)
	
	
	
	template <typename Integer>
	struct Implementation<Integer, 32>
	{
		static
		Integer genericFls(Integer v)
		{
			register EmoInt b = 32;
			register Integer t = v;
			
			if(!t)
				return -1;
			
			EMO_GENERIC_FLS_ELEMENTARY_CELL(32, 16);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(32, 8);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(32, 4);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(32, 2);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(32, 1);
			
			return b;
		}
		static inline
		Integer genericFfs(Integer v)
		{
			if(v == 0)
				return -1;
			return genericFls(v ^ (v - 1));
		}
		static inline
		Integer fls(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FLS32)
			return EMO_USE_CUSTOM_FLS32(v);
#elif defined(EMO_USE_CUSTOM_FLS64)
			return EMO_USE_CUSTOM_FLS64(v);
#else
			return genericFls(v);
#endif // defined(EMO_USE_CUSTOM_FLS32)
		}
		static inline
		Integer ffs(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FFS32)
			return EMO_USE_CUSTOM_FFS32(v);
#elif defined(EMO_USE_CUSTOM_FFS64)
			return EMO_USE_CUSTOM_FFS64(v);
#else
			return genericFfs(v);
#endif // defined(EMO_USE_CUSTOM_FLS32)
		}
	};
	
	
	
	template <typename Integer>
	struct Implementation<Integer, 16>
	{
		static
		Integer genericFls(Integer v)
		{
			register EmoInt b = 16;
			register Integer t = v;
			
			if(!t)
				return -1;
			
			EMO_GENERIC_FLS_ELEMENTARY_CELL(16, 8);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(16, 4);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(16, 2);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(16, 1);
			
			return b;
		}
		static inline
		Integer genericFfs(Integer v)
		{
			if(v == 0)
				return -1;
			return genericFls(v ^ (v - 1));
		}
		static inline
		Integer fls(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FLS16)
			return EMO_USE_CUSTOM_FLS16(v);
#elif defined(EMO_USE_CUSTOM_FLS32)
			return EMO_USE_CUSTOM_FLS32(v);
#elif defined(EMO_USE_CUSTOM_FLS64)
			return EMO_USE_CUSTOM_FLS64(v);
#else
			return genericFls(v);
#endif // defined(EMO_USE_CUSTOM_FLS16)
		}
		static inline
		Integer ffs(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FFS16)
			return EMO_USE_CUSTOM_FFS16(v);
#elif defined(EMO_USE_CUSTOM_FFS32)
			return EMO_USE_CUSTOM_FFS32(v);
#elif defined(EMO_USE_CUSTOM_FFS64)
			return EMO_USE_CUSTOM_FFS64(v);
#else
			return genericFfs(v);
#endif // defined(EMO_USE_CUSTOM_FFS16)
		}
	};
	
	
	
		template <typename Integer>
	struct Implementation<Integer, 8>
	{
		static
		Integer genericFls(Integer v)
		{
			register EmoInt b = 8;
			register Integer t = v;
			
			if(!t)
				return -1;
			
			EMO_GENERIC_FLS_ELEMENTARY_CELL(8, 4);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(8, 2);
			EMO_GENERIC_FLS_ELEMENTARY_CELL(8, 1);
			
			return b;
		}
		static inline
		Integer genericFfs(Integer v)
		{
			if(v == 0)
				return -1;
			return genericFls(v ^ (v - 1));
		}
		static inline
		Integer fls(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FLS8)
			return EMO_USE_CUSTOM_FLS8(v);
#elif defined(EMO_USE_CUSTOM_FLS16)
			return EMO_USE_CUSTOM_FLS16(v);
#elif defined(EMO_USE_CUSTOM_FLS32)
			return EMO_USE_CUSTOM_FLS32(v);
#elif defined(EMO_USE_CUSTOM_FLS64)
			return EMO_USE_CUSTOM_FLS64(v);
#else
			return genericFls(v);
#endif // defined(EMO_USE_CUSTOM_FLS8)
		}
		static inline
		Integer ffs(Integer v)
		{
#if defined(EMO_USE_CUSTOM_FFS8)
			return EMO_USE_CUSTOM_FFS8(v);
#elif defined(EMO_USE_CUSTOM_FFS16)
			return EMO_USE_CUSTOM_FFS16(v);
#elif defined(EMO_USE_CUSTOM_FFS32)
			return EMO_USE_CUSTOM_FFS32(v);
#elif defined(EMO_USE_CUSTOM_FFS64)
			return EMO_USE_CUSTOM_FFS64(v);
#else
			return genericFfs(v);
#endif // defined(EMO_USE_CUSTOM_FFS8)
		}
	};
};

EMO_END_INTERNAL_NAMESPACE

template <typename Integer>
inline
Integer EmoFls(const Integer v)
{
	return Intern::EmoFxs<Integer>::fls(v);
}

template <typename Integer>
inline
Integer EmoFfs(const Integer v)
{
	return Intern::EmoFxs<Integer>::ffs(v);
}

EMO_END_NAMESPACE

#endif // __EMO_FXS_H

