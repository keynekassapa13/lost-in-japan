cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    core/float4.cpp
    rt/primmod/instance.cpp
)

set(ASSIGNMENT_SOURCES
    core/float4.h
    core/matrix.cpp
    core/matrix.h
    rt/primmod/instance.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_instancing.cpp
)
