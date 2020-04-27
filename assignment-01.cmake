cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    core/color.cpp
    core/point.cpp
    core/vector.cpp
    rt/cameras/orthographic.cpp
    rt/cameras/perspective.cpp
    rt/ray.cpp
    rt/renderer.cpp
)

set(ASSIGNMENT_SOURCES
    core/assert.h
    core/color.h
    core/image.cpp
    core/image.h
    core/julia.cpp
    core/julia.h
    core/macros.h
    core/point.h
    core/scalar.cpp
    core/scalar.h
    core/vector.h
    core/float4.h
    rt/cameras/camera.h
    rt/cameras/orthographic.h
    rt/cameras/perspective.h
    rt/ray.h
    rt/renderer.h
    ${MY_ADDITIONAL_SOURCES}
	main/a_julia.cpp
	main/a_cameras.cpp
)
