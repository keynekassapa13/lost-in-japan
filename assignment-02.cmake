cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    rt/groups/simplegroup.cpp
    rt/integrators/casting.cpp
    rt/integrators/castingdist.cpp
    rt/solids/solid.cpp
    rt/solids/aabox.cpp
    rt/solids/disc.cpp
    rt/solids/infiniteplane.cpp
    rt/solids/quad.cpp
    rt/solids/sphere.cpp
    rt/solids/triangle.cpp
    rt/intersection.cpp
    rt/bbox.cpp
)

set(ASSIGNMENT_SOURCES
    rt/groups/group.h
    rt/groups/simplegroup.h
    rt/integrators/integrator.h
    rt/integrators/casting.h
    rt/integrators/castingdist.h
    rt/solids/solid.h
    rt/solids/aabox.h
    rt/solids/disc.h
    rt/solids/infiniteplane.h
    rt/solids/quad.h
    rt/solids/sphere.h
    rt/solids/triangle.h
    rt/bbox.h
    rt/intersection.h
    rt/primitive.h
    rt/world.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_solids.cpp
)
