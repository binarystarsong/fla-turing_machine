cmake_minimum_required (VERSION 2.8)

project (Turing)

aux_source_directory(. SRC_LIST)

add_executable(turing ${SRC_LIST})

