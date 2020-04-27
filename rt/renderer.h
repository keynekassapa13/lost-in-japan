#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <iostream>
#include <thread>

namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
    Renderer(Camera* cam, Integrator* integrator);
    void setSamples(uint samples) { this->samples = samples; }
    void render(Image& img);
    void test_render1(Image& img);
    void test_render2(Image& img);
    void rec(Image& img, uint w_start, uint w_end);
private:
    Image img_global;
    Camera* cam;
    Integrator* integrator;
    uint samples = 0;
};

}

#endif