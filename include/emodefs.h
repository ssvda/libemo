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

#	define EMO_C_STRUCT(NAME) \
		struct NAME; \
		typedef struct NAME NAME;

#else // __cplusplus

#	define EMO_BEGIN_NAMESPACE namespace Emo {
#	define EMO_END_NAMESPACE }

#	define EMO_C_STRUCT(NAME)

#endif // __cplusplus

#endif // __EMO_METAS_H

/**
	\internal
	\file emodefs.h
	
	\~english General LibEmo defenitions.
	
	\warning This is internal LibEmo's file. You didn't include it directly.
	
	\~russian Общие определения для LibEmo.
	
	\warning Это внутренний файл LibEmo. Вы не должны включать его непосредственно.
*/
/**
	\internal
	\def EMO_C_STRUCT
	
	\~english Prepare structure for using from C-sources.
	
	This macro should arived in header strongly \b before such structure defenitin.
	
	There is typical example of such structure:
	
	\~russian Подготавливает структуру для использования с языком C.
	
	Макрос должен быть расположен в заголовочном файле \b до определения структуры.
	
	Типичный пример определения такой структуры:
	
	\~
	
	\code
		EMO_C_STRUCT(MyStructure)
		
		struct MyStructure
		{
			int myCounter;
			MyStructure *pointerToMyself;
		};
	\endcode
*/
/**
	\internal
	\def EMO_BEGIN_NAMESPACE
	
	\~english Open the \ref Emo namespace for C++. Do nothing for C.
	
	\~russian В C++ начинает пространство имён \ref Emo. В C ничего не делает.
*/
/**
	\internal
	\def EMO_END_NAMESPACE
	
	\~english Close the \ref Emo namespace for C++. Do nothing for C.
	
	\~russian В C++ заканчивает пространство имён \ref Emo. В C ничего не делает.
*/
