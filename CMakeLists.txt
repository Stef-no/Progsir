cmake_minimum_required(VERSION 3.16.3) 
project(Epidemic VERSION 0.1.0)

include(CTest)

set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined " "-fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined " "-fno-omit-frame-pointer")

add_executable(epidemic my_epidemic.cpp sir_epidemic.cpp main.cpp)

if (BUILD_TESTING)
    add_executable(epidemic.t my_epidemic.cpp my_epidemic.test.cpp)
    add_executable(sir.t sir_epidemic.cpp sir_epidemic.test.cpp)

    add_test(NAME epidemic.t COMMAND epidemic.t)
    add_test(NAME sir.t COMMAND sir.t)

endif()