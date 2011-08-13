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

#ifndef __EMO_DEFS_H
#define __EMO_DEFS_H

#ifndef __cplusplus

#	define EMO_BEGIN_NAMESPACE
#	define EMO_END_NAMESPACE

#	define EMO_BEGIN_INTERNAL_NAMESPACE
#	define EMO_END_INTERNAL_NAMESPACE

#	define EMO_C_STRUCT(NAME) \
		struct NAME; \
		typedef struct NAME NAME;
#	define EMO_EXTERN_C extern "C"
#	define EMO_INLINE inline

#else // __cplusplus

#	define EMO_BEGIN_NAMESPACE namespace Emo {
#	define EMO_END_NAMESPACE }

#	define EMO_BEGIN_INTERNAL_NAMESPACE namespace Intern {
#	define EMO_END_INTERNAL_NAMESPACE }

#	define EMO_C_STRUCT(NAME)
#	define EMO_EXTERN_C
#	if defined(EMO_WITH_TRUE_INLINE) || defined(__GNUC__)
#		define EMO_INLINE inline
#	else // EMO_WITH_TRUE_INLINE
#endif

#endif // __cplusplus

#ifndef EMO_BITS_IN_TYPE
#	define EMO_BITS_IN_TYPE(TYPE) (8 * sizeof(TYPE))
#endif //EMO_BITS_IN_TYPE

#ifndef EMO_BUS_WIDTH
#	define EMO_BUS_WIDTH EMO_BITS_IN_TYPE(int)
#endif // EMO_BUS_WIDTH

#endif // __EMO_DEFS_H
