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

#ifndef __EMO_SIGNAL_H
#define __EMO_SIGNAL_H

#include <emodefs.h>
#include <emotypes.h>
#include <emosignalinternals.h>

EMO_BEGIN_NAMESPACE

// Forward declarations
class EmoObject;
class EmoSlotBase;

EMO_BEGIN_INTERNAL_NAMESPACE

template <typename SignalType>
inline
void emoCall(SignalType &signal,
             void **arguments)
{
	signal.call(arguments);
}

EMO_END_INTERNAL_NAMESPACE

template <typename SignalMasterType,
          typename SignalInternals /*= EmoDefaultSignalInternals*/>
class EmoSignal
{
	template <typename SignalType>
	friend Intern::emoCall(SignalType, void **);
	
public:
	typedef SignalMasterType MasterType;
	
	inline
	void bind(EmoSlotBase *slot, EmoObject *reciver)
	{
		this->m_int.bind(EmoBinding(slot, reciver));
	}
	
	inline
	void unbind(EmoSlotBase *slot, EmoObject *reciver)
	{
		this->m_int.unbind(EmoBinding(slot, reciver));
	}
	
private:
	inline
	void call(void **a)
	{
		this->m_int.call(a);
	}
	
	SignalInternals m_int;
};

EMO_END_NAMESPACE

#endif // __EMO_SIGNAL_H
