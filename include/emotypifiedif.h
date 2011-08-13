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

#ifndef __EMO_TYPIFIEDIF_H
#define __EMO_TYPIFIEDIF_H

#include <emodefs.h>
#include <emotypes.h>

EMO_BEGIN_NAMESPACE

EMO_BEGIN_INTERNAL_NAMESPACE

template <EmoBool Condition,
          typename TypeIfTrue,
          typename TypeIfFalse>
struct EmoTypifiedIf
{
};

template <typename TypeIfTrue,
          typename TypeIfFalse>
struct EmoTypifiedIf<true, TypeIfTrue, TypeIfFalse>
{
	typedef TypeIfTrue Type;
};

template <typename TypeIfTrue,
          typename TypeIfFalse>
struct EmoTypifiedIf<false, TypeIfTrue, TypeIfFalse>
{
	typedef TypeIfFalse Type;
};

EMO_END_INTERNAL_NAMESPACE

EMO_END_NAMESPACE

#define EMO_TYPIFIED_IF(CONDITION,TYPEIFTRUE,TYPEIFFALSE) \
		Emo::Intern::EmoTypifiedIf<(CONDITION), TYPEIFTRUE, TYPEIFFALSE >::Type

#endif // __EMO_TYPIFIEDIF_H

