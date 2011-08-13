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

#ifndef __EMO_NUMERICLIMITS_H
#define __EMO_NUMERICLIMITS_H

#include <emodefs.h>
#include <emotypes.h>
#include <emotypifiedif.h>

EMO_BEGIN_NAMESPACE

EMO_BEGIN_INTERNAL_NAMESPACE

// If we want best fit type is not less then...
#ifndef EMO_LIMIT_BEST_FIT_INT_WITH
#	define EMO_LIMIT_BEST_FIT_INT_WITH TypeD
#endif // EMO_LIMIT_BEST_FIT_INT_WITH

template <EmoSizeType NumberOfBits>
class EmoBestFitInt
{
private:
	// We suppose that this types align descending.
	typedef long  TypeA;
	typedef int   TypeB;
	typedef short TypeC;
	typedef char  TypeD;
	typedef EMO_LIMIT_BEST_FIT_INT_WITH TypeL;
	
	enum
	{
		BitsA = EMO_BITS_IN_TYPE(TypeA),
		BitsB = EMO_BITS_IN_TYPE(TypeB),
		BitsC = EMO_BITS_IN_TYPE(TypeC),
		BitsD = EMO_BITS_IN_TYPE(TypeD),
		BitsX = NumberOfBits > EMO_BITS_IN_TYPE(TypeL) ? NumberOfBits : EMO_BITS_IN_TYPE(TypeL)
	};
	
	// Series of comporations.
	//typedef typename EmoTypifiedIf<(BitsX > BitsD), TypeC, TypeD>::Type Step1Type;
	//typedef typename EmoTypifiedIf<(BitsX > BitsC), TypeB, Step1Type>::Type Step2Type;
	//typedef typename EmoTypifiedIf<(BitsX > BitsB), TypeA, Step2Type>::Type Step3Type;
	//typedef typename EmoTypifiedIf<(BitsX > BitsA), void, Step3Type>::Type BestFitType;
	
	typedef typename EMO_TYPIFIED_IF(BitsX > BitsD, TypeC, TypeD)     Step1Type;
	typedef typename EMO_TYPIFIED_IF(BitsX > BitsC, TypeB, Step1Type) Step2Type;
	typedef typename EMO_TYPIFIED_IF(BitsX > BitsB, TypeA, Step2Type) Step3Type;
	
public:
	typedef typename EMO_TYPIFIED_IF(BitsX > BitsA, void, Step3Type) BestFitType;
};

EMO_END_INTERNAL_NAMESPACE

EMO_END_NAMESPACE

#ifndef EMO_FORCE_BEST_FIT_INT_TO
#	define EMO_BEST_FIT_INT(BITS) Emo::Intern::EmoBestFitInt<BITS>::BestFitType
#else // EMO_FORCE_BEST_FIT_INT_TO
#define EMO_BEST_FIT_INT(BITS) EMO_FORCE_BEST_FIT_INT_TO
#endif // EMO_FORCE_BEST_FIT_INT_TO

#endif // __EMO_NUMERICLIMITS_H

