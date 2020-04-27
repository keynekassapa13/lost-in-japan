#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    this->clr = RGBColor::rep(0.0f);
}

ConstantTexture::ConstantTexture(const RGBColor& color)
{
    this->clr = color;
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    return clr;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

}