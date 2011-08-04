# tz-lom too lazy to comment
# lol

project (UnitTest)

macro (register_unit_test)
    EmoInternBuildFullPathedList (EMO_INTERN_UNITTESTS_FILES ARGV ${CMAKE_CURRENT_SOURCE_DIR})
    set (EMO_UNITTESTS_FILES ${EMO_UNITTESTS_FILES} ${EMO_INTERN_UNITTESTS_FILES})
endmacro (register_unit_test)


find_package (LibEmo REQUIRED)
find_package (CppUnit REQUIRED)

include_directories(SYSTEM ${CPPUNIT_INCLUDE_DIR})

add_executable (${PROJECT_NAME}
    tests.cpp
    ${EMO_UNITTESTS_FILES}
)

target_link_libraries (${PROJECT_NAME}
    ${CPPUNIT_LIBRARY}
    Emo
)
