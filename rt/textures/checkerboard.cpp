#include <rt/textures/checkerboard.h>
#include <math.h>
#include <core/point.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    this->w = white;
    this->b = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {

    int lx = floor(coord.x * 2);
    int ly = floor(coord.y * 2);
    int lz = floor(coord.z * 2);

    int p = abs(lx + ly + lz) % 2;
    if (p == 1) {return b;}
    return w;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

}