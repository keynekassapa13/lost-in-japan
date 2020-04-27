cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    rt/groups/bvh.cpp
)

set(ASSIGNMENT_SOURCES
    rt/groups/bvh.h
    rt/groups/kdtree.h
    rt/loaders/obj.cpp
    rt/loaders/obj.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_indexing.cpp
)

file(COPY
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
