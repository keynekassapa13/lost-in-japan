#include <core/point.h>
#include <core/vector.h>
#include <core/color.h>
#include <core/scalar.h>
#include <core/julia.h>
#include <core/image.h>
#include <rt/renderer.h>

using namespace rt;

float a1computeWeight(float fx, float fy, const Point& c, float div) {
    Point v(fx, fy, 0.5f);
    v = v - Vector::rep(0.5f);
    v = v * 2.0f;
    int numIter = julia(v, c);
    return numIter/(numIter+div);
}

RGBColor a1computeColor(uint x, uint y, uint width, uint height) {
    float fx =  float(x) / float(width);
    float fy =  float(y) / float(height);
    RGBColor color = RGBColor::rep(0.0f);
    color = color + a1computeWeight(fx, fy, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
    color = color + a1computeWeight(fx, fy, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
    color = color + a1computeWeight(fy, fx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.2f, 0.3f, 0.4f);
    return RGBColor::rep(1.0f) - color;
}

void a_julia() {
    Image img(800, 800);
    Renderer engine(0,0);
    engine.test_render1(img);
    img.writePNG("a1.png");
}