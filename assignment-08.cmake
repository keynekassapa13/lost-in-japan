cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    rt/primmod/bmap.cpp
    rt/primmod/bmap.h
    rt/volume.h
    rt/lights/ambient.h
    rt/lights/ambient.cpp
    ${MY_ADDITIONAL_SOURCES}
    main/a_bump.cpp
    main/a_volume.cpp
)

file(COPY
    models/stones_bump.png
    models/stones_spec.png
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
