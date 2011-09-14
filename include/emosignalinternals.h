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

#ifndef __EMO_SIGNALINTRNALS_H
#define __EMO_SIGNALINTRNALS_H

#include <emodefs.h>
#include <emotypes.h>
#include <emobinding.h>
#include <emomemory.h>
#include <emometacontainer.h>
#include <emobindinglistnode.h>
#include <emobindinglist.h>

EMO_BEGIN_NAMESPACE

template <EmoAllocationType AllocationType,
          unsigned int FirstPortion,
          unsigned int ExtendPortion>
class EmoSignalInternals
{
public:
	typedef EmoBindingList<FirstPortion, ExtendPortion> ListType;
	
	inline
	void bind(EmoBinding *source)
	{
		this->m_container.element().bind(source);
	}
	
	inline
	void unbind(EmoBinding *pattern)
	{
		this->m_container.element().unbind(pattern);
	}
	
	inline
	void call(void **a)
	{
		this->m_container.element().call(a);
	}
	
private:
	EmoMetaContainer<ListType, AllocationType> m_container;
};

EMO_END_NAMESPACE

#endif // __EMO_SIGNALINTRNALS_H
