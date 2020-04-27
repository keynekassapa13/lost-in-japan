cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    ${MY_ADDITIONAL_SOURCES}
    main/a_competition.cpp
)

file(COPY
    models/stones_bump.png
    models/stones_spec.png
    models/japanHouse.obj
    models/man.obj
    models/building.obj
    models/buildingadd.obj
    DESTINATION ${CMAKE_BINARY_DIR}/models
)

file(COPY
    models/tex/Concrete.png
    models/tex/concrete1.png
    models/tex/grass.png
    models/tex/int_blue.png
    models/tex/plastic2.png
    models/tex/wood.png
    models/tex/wood3.png
    DESTINATION ${CMAKE_BINARY_DIR}/models/tex
)
