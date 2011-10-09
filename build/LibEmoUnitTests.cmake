################################################################################
# Embeded Meta Objects (EMO) Library
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


#
# Macro to regster UnitTest
#

macro (register_unit_test)
	set (EMO_INTERN_ARGV ${ARGV})
	EmoInternBuildFullPathedList (EMO_INTERN_UNITTESTS_FILES EMO_INTERN_ARGV "${CMAKE_CURRENT_SOURCE_DIR}")
# Add to list of requred files
	list (APPEND EMO_UNITTESTS_FILES ${EMO_INTERN_UNITTESTS_FILES})
	list (GET EMO_INTERN_UNITTESTS_FILES 0 EMO_INTERN_UNITTEST_NAME)
# Add to list of fixtures
	list (APPEND EMO_UNITTESTS_FIXTURES ${EMO_INTERN_UNITTEST_NAME})
	set (EMO_UNITTESTS_FILES ${EMO_UNITTESTS_FILES} PARENT_SCOPE)
	set (EMO_UNITTESTS_FIXTURES ${EMO_UNITTESTS_FIXTURES} PARENT_SCOPE)
endmacro (register_unit_test)


#
# Macro to create UnitTest project
#

macro (generate_unit_test)

# Generate header with all UnitTest fixtures
foreach (EMO_INTERN_H_ITEM ${EMO_UNITTESTS_FIXTURES})
	list (APPEND EMO_INTERN_H "#include \"${EMO_INTERN_H_ITEM}\"\n")
endforeach (EMO_INTERN_H_ITEM)
file (WRITE "UnitTests.generated.h" ${EMO_INTERN_H})

# Define project name
project (UnitTest)

# Find libraries
find_package (LibEmo REQUIRED)
find_package (CppUnit REQUIRED)

# Include CppUnit
include_directories(SYSTEM ${CPPUNIT_INCLUDE_DIR})

add_executable (${PROJECT_NAME}
	tests.cpp
	${EMO_UNITTESTS_FILES}
)

# Add dependency from Emo and CppUnit
target_link_libraries (${PROJECT_NAME}
	${CPPUNIT_LIBRARY}
	Emo
)

if (EMO_RUN_TESTS_64)

	add_executable (${PROJECT_NAME}64
		tests64.cpp
		${EMO_UNITTESTS_FILES}
	)

	target_link_libraries (${PROJECT_NAME}64
		${CPPUNIT_LIBRARY}
		Emo
	)

endif (EMO_RUN_TESTS_64)


# Enable code coverage
if (EMO_CODE_COVERAGE)
	set (CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
	target_link_libraries (${PROJECT_NAME} gcov)
	if (EMO_RUN_TESTS_64)
		target_link_libraries (${PROJECT_NAME}64 gcov)
	endif (EMO_RUN_TESTS_64)
endif (EMO_CODE_COVERAGE)

# Run unit tests
if (EMO_RUN_TESTS)
	add_custom_target (test ALL $<TARGET_FILE:UnitTest>
		WORKING_DIRECTORY ${EMO_BUILD_DIR}/tests
		DEPENDS ${PROJECT_NAME}
	)

	if (EMO_RUN_TESTS_64)
		add_custom_target (test64 ALL $<TARGET_FILE:UnitTest64>
			WORKING_DIRECTORY ${EMO_BUILD_DIR}/tests
			DEPENDS ${PROJECT_NAME}64
		)
	endif (EMO_RUN_TESTS_64)
else (EMO_RUN_TESTS)
	add_custom_target (test $<TARGET_FILE:UnitTest>
		WORKING_DIRECTORY ${EMO_BUILD_DIR}/tests
		DEPENDS ${PROJECT_NAME}
	)

	if (EMO_RUN_TESTS_64)
		add_custom_target (test64 $<TARGET_FILE:UnitTest64>
			WORKING_DIRECTORY ${EMO_BUILD_DIR}/tests
			DEPENDS ${PROJECT_NAME}64
		)
	endif (EMO_RUN_TESTS_64)
endif (EMO_RUN_TESTS)

endmacro (generate_unit_test)
