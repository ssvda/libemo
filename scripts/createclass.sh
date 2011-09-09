#! /bin/bash
################################################################################
# LibEmo developer's script: creating of new class.
#
# Copyright (C) 2011  Dmitry A. Sysoev
# Copyright (C) 2011  Yuri O. Nuzhdin
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
################################################################################

MYSELF="$(basename "$0")"
EMOROOT="$(cd "$(dirname "$0")/.."; pwd)"

ARGS=$(getopt --name="$MYSELF" \
	--options="tiQ" \
	--longoptions="help,template" \
	-- "$@")

[ $? -ne 0 ] && exit 1
eval set -- "$ARGS"
HELP="$(cat <<EOF
[OPTIONS] [--] CLASSNAME
Create a new class in LibEmo
Options:
  -t, --template        Don't create a corresponding .cpp file.
  -i, --internal        Mark file as internal.
  -Q, --qtstyle         Also create a Qt-style CamelCase header.
  --help                Print this message.
Returns:
  1 --- Improper option or argument.
  2 --- Some files already exists.
EOF
)"

TEMPLATE=0
INTERNAL=0
QTSTYLE=0

while [ $# -gt 0 ]
do
	case "$1" in
		--help)
			echo "$MYSELF" "$HELP"
			exit ;;
		-t|--template)
			TEMPLATE=1 ;;
		-i|--internal)
			INTERNAL=1 ;;
		-Q|--qtstyle)
			QTSTYLE=1 ;;
		--)
			shift
			CLASSNAME="$1";;
	esac
	shift
done

################################################################################

# Each class of LibEmo _must_ begins with Emo.
if [ ${#CLASSNAME} -le 3 ] || [ ${CLASSNAME:0:3} != "Emo" ]
then
	echo "$MYSELF: Each class of LibEmo _must_ begins with Emo" >&2
	exit 1
fi

# Test for upper case character right after Emo prefix.
if [ ${#CLASSNAME} -le 4 ] || echo "${CLASSNAME:3:1}" | LC_ALL=C grep -qG '[^A-Z]'
then
	echo "$MYSELF: LibEmo use a CamelCase convention for classes" >&2
	exit 1
fi

# Create a lowercase name
LCNAME="$(echo "$CLASSNAME" |perl -e 'print lc(<>)')"
# Create a uppercase name without Emo prefix
UCNAME="$(echo "$CLASSNAME" |perl -e 'print uc(<>)')"
UCNAME="${UCNAME:3}"

HFILE="$EMOROOT/include/$LCNAME.h"
QTFILE="$EMOROOT/include/$CLASSNAME"
CPPFILE="$EMOROOT/libemo/$LCNAME.cpp"
DOXFILE="$EMOROOT/doc/$LCNAME.dox"

EMOFILELIST="$EMOROOT/build/LibEmoFiles.cmake"
EMOCMAKELIST="$EMOROOT/build/CMakeLists.txt"

# Test for heareds existense.
if [ -a "$HFILE" ] || [ -a "$QTFILE" ] || [ -a "$CPPFILE" ] || [ -a "$DOXFILE" ]
then
	echo "$MYSELF: Some files are already exists. Aborting." >&2
	echo "$MYSELF: Check for file \`$HFILE'" >&2
	echo "$MYSELF: Check for file \`$QTFILE'" >&2
	echo "$MYSELF: Check for file \`$CPPFILE'" >&2
	echo "$MYSELF: Check for file \`$DOXFILE'" >&2
	exit 2
fi

if [ $INTERNAL -eq 1 ]
then
	INTERNAL_INC='\internal
'
else
	INTERNAL_INC=''
fi

LICENSE="$(cat <<EOF
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
EOF
)"

# Form a header file
HHEADER="$LICENSE

#ifndef __EMO_${UCNAME}_H
#define __EMO_${UCNAME}_H

#include <emodefs.h>

EMO_BEGIN_NAMESPACE

class $CLASSNAME
{
public:
	$CLASSNAME();
};

EMO_END_NAMESPACE

#endif // __EMO_${UCNAME}_H
"

# Form a Qt-style header
QTHEADER="$LICENSE

#include <$LCNAME.h>
"

# Form a cpp file
CPPHEADER="$LICENSE

#include <$LCNAME.h>

EMO_BEGIN_NAMESPACE

$CLASSNAME::$CLASSNAME()
{
}

EMO_END_NAMESPACE

"

# Form a doxygen file
DOXHEADER="Embeded Meta Objects (EMO) Library

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

/**
$INTERNAL_INC\\file $LCNAME.h

\~english \brief 

\~russian \brief 
*/

"

# Writing a files

echo "$MYSELF: Writing header template to \`$HFILE'"
echo "$HHEADER" >> "$HFILE"

if [ $QTSTYLE == 1 ]
then
	echo "$MYSELF: Writing Qt-style header template to \`$QTFILE'"
	echo "$QTHEADER" >> "$QTFILE"
fi

if [ $TEMPLATE == 0 ]
then
	echo "$MYSELF: Writing Qt-style header template to \`$CPPFILE'"
	echo "$CPPHEADER" >> "$CPPFILE"
fi

echo "$MYSELF: Writing doxygen documentation template to \`$DOXFILE'"
echo "$DOXHEADER" >> "$DOXFILE"

# Update project files
SEDSCRIPT="
	s#set (EMO_CSTYLE_HEADERS_LIST#set (EMO_CSTYLE_HEADERS_LIST\n\t$LCNAME.h#
	s#set (EMO_SOURCES_DOX_LIST#set (EMO_SOURCES_DOX_LIST\n\t$LCNAME.dox#
"

if [ $QTSTYLE == 1 ]
then
	SEDSCRIPT="$SEDSCRIPT
	s#set (EMO_QTSTYLE_HEADERS_LIST#set (EMO_QTSTYLE_HEADERS_LIST\n\t$CLASSNAME#
"
fi

if [ $TEMPLATE == 0 ]
then
	SEDSCRIPT="$SEDSCRIPT
	s#set (EMO_SOURCES_LIST#set (EMO_SOURCES_LIST\n\t$LCNAME.cpp#
"
fi

echo "$MYSELF: Patching \`$EMOFILELIST'..."

cat "$EMOFILELIST" > "$EMOFILELIST.backup"

sed --in-place "$SEDSCRIPT" "$EMOFILELIST"
touch -a -c "$EMOCMAKELIST"

echo "$MYSELF: Reserve copy was saved to \`$EMOFILELIST.backup'..."

