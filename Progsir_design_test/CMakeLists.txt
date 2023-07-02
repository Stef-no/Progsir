cmake_minimum_required(VERSION 3.16.3) project(Epidemic VERSION 0.1.0)

#abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
    include(CTest)

        set(CMAKE_CXX_COMPILER g++ - 10)

            set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
                set(CMAKE_CXX_STANDARD 17) set(
                    CMAKE_CXX_STANDARD_REQUIRED ON) set(CMAKE_CXX_EXTENSIONS ON)

#abilita warning
                    string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

#abilita l 'address sanitizer e l' undefined - behaviour sanitizer in debug mode
                        string(APPEND CMAKE_CXX_FLAGS_DEBUG
                               " -fsanitize=address,undefined "
                               "-fno-omit-frame-pointer")
                            string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG
                                   " -fsanitize=address,undefined "
                                   "-fno-omit-frame-pointer")

                                add_executable(
                                    my_epidemic my_epidemic.cpp my_main.cpp)

                                    add_executable(sir_epidemic sir_epidemic
                                                       .cpp sir_main.cpp)

#se il testing e' abilitato...
#per disabilitare il testing, \
    passare - DBUILD_TESTING = OFF a cmake durante la fase di configurazione
                                        if (BUILD_TESTING)

                                            add_executable(
                                                epidemic.t my_epidemic
                                                    .cpp my_epidemic.test.cpp)
                                                add_executable(
                                                    sir.t sir_epidemic
                                                        .cpp sir_epidemic.test
                                                        .cpp)

#aggiungi l'eseguibile alla lista dei test
                                                    add_test(NAME epidemic
                                                                 .t COMMAND
                                                                     epidemic.t)
                                                        add_test(NAME sir
                                                                     .t COMMAND
                                                                         sir.t)

                                                            endif()