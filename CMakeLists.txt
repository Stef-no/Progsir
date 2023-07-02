cmake_minimum_required(VERSION 3.24.3) project(MyEpidemic)

#Imposta la versione C++
    set(CMAKE_CXX_STANDARD 14)

#Trova le librerie SFML
        find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

#Aggiungi gli eseguibili
            add_executable(Simulation.out my_epidemic.cpp my_graph.cpp)

#Collega le librerie SFML
                target_compile_options(Simulation.out PRIVATE - Wall - Wextra -
                                       g)
#target_link_options(Simulation.out Private - fsanitize = address)
                    target_link_libraries(Simulation.out sfml - graphics sfml -
                                          window sfml - system)
