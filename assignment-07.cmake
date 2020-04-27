cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    core/random.cpp
    core/random.h
    rt/materials/fuzzymirror.cpp
    rt/materials/fuzzymirror.h
    rt/materials/glass.cpp
    rt/materials/glass.h
    rt/cameras/dofperspective.cpp
    rt/cameras/dofperspective.h
    rt/lights/arealight.cpp
    rt/lights/arealight.h
    rt/loaders/objmat.cpp
    rt/solids/striangle.cpp
    rt/solids/striangle.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_distributed.cpp
    main/a_smooth.cpp
    rt/motionblur.h
)
