cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    rt/materials/dummy.cpp
    rt/lights/directional.cpp
    rt/lights/pointlight.cpp
    rt/lights/spotlight.cpp
    rt/lights/projective.cpp
    rt/integrators/raytrace.cpp
)

set(ASSIGNMENT_SOURCES
    rt/materials/material.h
    rt/materials/dummy.h
    rt/lights/light.h
    rt/lights/directional.h
    rt/lights/pointlight.h
    rt/lights/spotlight.h
    rt/lights/projective.h
    rt/integrators/raytrace.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_lighting.cpp
)
