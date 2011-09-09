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

#ifndef __EMO_SIGNED_H
#define __EMO_SIGNED_H

#include <emodefs.h>

EMO_BEGIN_NAMESPACE

template <typename Integer>
class EmoSigned
{
private:
	EmoSigned();
};

// This macroes used to reduse number of copy-paste operations.
// It's only suitable for use with this context and shouldn't
// be used in any other places.
#define EMO_SIGNED_CLASS_SPECIFICATION(TYPE, SIGNED, UNSIGNED) \
		template <> \
		class EmoSigned<TYPE> \
		{ \
		public: \
			typedef SIGNED SignedType; \
			typedef UNSIGNED UnsignedType; \
		};

EMO_SIGNED_CLASS_SPECIFICATION(signed char,      signed char,  unsigned char)
EMO_SIGNED_CLASS_SPECIFICATION(unsigned char,    signed char,  unsigned char)

EMO_SIGNED_CLASS_SPECIFICATION(signed short,     signed short, unsigned short)
EMO_SIGNED_CLASS_SPECIFICATION(unsigned short,   signed short, unsigned short)

EMO_SIGNED_CLASS_SPECIFICATION(signed int,       signed int,   unsigned int)
EMO_SIGNED_CLASS_SPECIFICATION(unsigned int,     signed int,   unsigned int)

EMO_SIGNED_CLASS_SPECIFICATION(signed long,      signed long,  unsigned long)
EMO_SIGNED_CLASS_SPECIFICATION(unsigned long,    signed long,  unsigned long)

#undef EMO_SIGNED_CLASS_SPECIFICATION

EMO_END_NAMESPACE

#endif // __EMO_SIGNED_H

