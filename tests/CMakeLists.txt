include_directories(../src)

include_directories(.)

add_executable(tests
        StringTest.cpp

        ../src/String.h
        ../src/String.cpp
        )
