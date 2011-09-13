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
#include <emomemory.h>
#include <emometacontainer.h>

EMO_BEGIN_NAMESPACE

// Forward declarations
class EmoObject;
class EmoSlotBase;

/*
	Задачи внутренностей сигнала:
	 - Хранить список соединений в выбранной форме
	 - Осуществлять вставку в список.
	    bind()
	 - Осуществлять удаление из списка.
	    unbind()
	    clear()
	 - Осуществлять рассылку по всем элементам списка.
	    emit()
*/

template <EmoAllocationType p_AllocationType,
          unsigned int p_FirstPortion,
          unsigned int p_ExtendPortion>
class EmoSignalInternalsBaseс
{
public:
	enum
	{
		AllocationType = p_AllocationType,
		FirstPortion = p_FirstPortion,
		ExtendPortion = p_ExtendPortion
	};
	
protected:
	typedef unsigned int ListStateType;
	
	struct ListExtend
	{
		EmoBinding m_list[ExtendPortion];
		ListExtend *m_next;
	};
	
	struct ListHead
	{
		ListStateType m_state;
		EmoBinding m_list[FirstPortion];
		ListExtend *m_next;
	};
	
	typedef ListExtend *IterationState;
	
	inline
	EmoBinding *allocate();
	inline
	void free(EmoBinding *binding);
	inline
	void iterate(IterationState *state);
	inline
	EmoBinding *next(IterationState *state);
	
public:
	void clear();
};

template <EmoAllocationType p_AT,
          unsigned int p_FP,
          unsigned int p_EP>
EmoBinding *EmoSignalInternalsBase<p_AT, p_FP, p_EP>::allocate()
{
	
}

template <EmoAllocationType p_AllocationType,
          unsigned int p_FirstPortion,
          unsigned int p_ExtendPortion>
class EmoSignalInternals
	:public EmoSignalInternalsBase<p_AllocationType, p_FirstPortion, p_ExtendPortion>
{
public:
};

typedef EmoSignalInternals<DynamicalAllocation, 2, 2>  EmoDefaultSignalInternals;
typedef EmoSignalInternals<StaticalAllocation, 1, 1>   EmoTinySignalInternals;
typedef EmoSignalInternals<DynamicalAllocation, 0, 2>  EmoDynamicalSignalInternals;
typedef EmoSignalInternals<StaticalAllocation, 4, 0>   EmoStaticalSignalInternals;
typedef EmoSignalInternals<DynamicalAllocation, 4, 4>  EmoHugeSignalInternals;

EMO_END_NAMESPACE

#endif // __EMO_SIGNALINTRNALS_H
