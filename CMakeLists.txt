CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(CustomDataStructures VERSION 1.0.0)

INCLUDE_DIRECTORIES(include)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

SET(SOURCES 
    src/Vector.cpp
    src/List.cpp
    src/Stack.cpp
    src/Queue.cpp
    src/Heap.cpp
    src/Hashmap.cpp
    src/Trie.cpp)

ADD_LIBRARY(${PROJECT_NAME} SHARED
    ${SOURCES})