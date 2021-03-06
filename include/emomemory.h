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

#ifndef __EMO_MEMORY_H
#define __EMO_MEMORY_H

#include <emodefs.h>
#include <emotypes.h>

#if   defined(EMO_USE_STD_ALLOCATOR)
// Use new and delete operators. There is nothing to include.
#elif defined(EMO_USE_C_ALLOCATOR)
// Use malloc and free functions.
#	include <cstdlib>
#elif defined(EMO_USE_CUSTOM_ALLOCATOR)
// User must provide pair of defenition for allocating and freeing memory.
#	if !defined(EMO_USE_CUSTOM_MALLOC) || !defined(EMO_USE_CUSTOM_FREE)
#		error "EMO_USE_CUSTOM_MALLOC or EMO_USE_CUSTOM_FREE is not provided"
#	endif // !defined(EMO_USE_CUSTOM_MALLOC) || !defined(EMO_USE_CUSTOM_FREE)
// User can specify special file to include allocator.
#	if defined(EMO_CUSTOM_ALLOCATOR_INCLUDE)
#		include EMO_CUSTOM_ALLOCATOR_INCLUDE
#	endif
#elif defined(EMO_USE_BUILDIN_ALLOCATOR)
#	if defined(EMO_HAS_BUILDIN_ALLOCATOR)
#		error "LibEmo build-in allocator is not implemented yet"
#	else // defined(EMO_HAS_BUILDIN_ALLOCATOR)
#		error "This version of LibEmo does not compiled with build-in allocator"
#	endif // defined(EMO_HAS_BUILDIN_ALLOCATOR)
#else
// There is no allocator selected. Using standard C++ operators.
#	define EMO_USE_STD_ALLOCATOR
#endif // defined(EMO_USE_STD_ALLOCATOR)

#if   defined(EMO_USE_STD_MEMOP)
#	include <cstring>
#elif defined(EMO_USE_BUILDIN_MEMOP)
#	if defined(EMO_HAS_BUILDIN_MEMOP)
#		error "LibEmo build-in memory operations is not implemented yet"
#	else // defined(EMO_HAS_BUILDIN_MEMOP)
#		error "This version of LibEmo does not compiled with build-in memory operations"
#	endif // defined(EMO_HAS_BUILDIN_MEMOP)
#elif defined(EMO_USE_CUSTOM_MEMOP)
// User must provide defenitions for operations on memory.
#	if !defined(EMO_CUSTOM_MEMSET) || !defined(EMO_CUSTOM_MEMCPY)
#		error "EMO_CUSTOM_MEMSET or EMO_CUSTOM_MEMCPY is not provided"
#	endif
// User can specify special file to include memory operations.
#	if defined(EMO_CUSTOM_MEMOP_INCLUDE)
#		include EMO_CUSTOM_MEMOP_INCLUDE
# endif // defined(EMO_CUSTOM_MEMOP_INCLUDE)
#else // defined(EMO_USE_STD_MEMOP)
#	define EMO_USE_STD_MEMOP
#	include <cstring>
#endif // defined(EMO_USE_STD_MEMOP)

EMO_BEGIN_NAMESPACE

inline
void *emoDoMalloc(Emo::EmoSizeType size)
{
#if   defined(EMO_USE_STD_ALLOCATOR)
	return ::operator new(size);
#elif defined(EMO_USE_C_ALLOCATOR)
	return std::malloc(size);
#elif defined(EMO_USE_CUSTOM_ALLOCATOR)
	return EMO_USE_CUSTOM_MALLOC(size);
#elif defined(EMO_USE_BUILDIN_ALLOCATOR)
#endif // defined(EMO_USE_STD_ALLOCATOR)
}

inline
void emoDoFree(void *pointer)
{
#if   defined(EMO_USE_STD_ALLOCATOR)
	::operator delete(pointer);
#elif defined(EMO_USE_C_ALLOCATOR)
	std::free(pointer);
#elif defined(EMO_USE_CUSTOM_ALLOCATOR)
	EMO_USE_CUSTOM_FREE(pointer);
#elif defined(EMO_USE_BUILDIN_ALLOCATOR)
#endif // defined(EMO_USE_STD_ALLOCATOR)
}

template <typename Type>
inline
void emoDestruct(Type *object)
{
	object->~Type();
}

#define EMO_NEW(TYPE) new(emoDoMalloc(sizeof(TYPE))) TYPE
#define emoNew EMO_NEW

template <typename Type>
inline
Type *emoAlloc()
{
	return new(emoDoMalloc(sizeof(Type))) Type();
}

template <typename Type>
inline
Type *emoAlloc(const Type &that)
{
	return new(emoDoMalloc(sizeof(Type))) Type(that);
}

template <typename Type>
inline
void emoDelete(Type *object)
{
	object->~Type();
	emoDoFree(object);
}

template <>
inline
void emoDelete<void>(void *object)
{
	emoDoFree(object);
}

inline
void *emoMemSet(void *buf,
                EmoByte val,
                EmoSizeType size)
{
#if   defined(EMO_USE_STD_MEMOP)
	return std::memset(buf, val, size);
#elif defined(EMO_USE_BUILDIN_MEMOP)
#elif defined(EMO_USE_CUSTOM_MEMOP)
	return EMO_CUSTOM_MEMSET(buf, val, size);
#endif // defined(EMO_USE_STD_MEMOP)
}

EMO_END_NAMESPACE

#endif // __EMO_MEMORY_H
