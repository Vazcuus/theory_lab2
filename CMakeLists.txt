cmake_minimum_required(VERSION 3.5.0)
project(lab2 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab2 
    main.cpp
    huffman_code.h
    huffman_tree_node.h
    node.h
    shanon.h
)
add_executable(lab2_3 ex3.cpp)

