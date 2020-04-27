#include <rt/textures/imagetex.h>
#include <math.h>
#include <core/point.h>
#include <core/vector.h>

namespace rt {

ImageTexture::ImageTexture()
{
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    this->img.readPNG(filename);
    this->bh = bh;
    this->i = i;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    this->img = image;
    this->bh = bh;
    this->i = i;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    int lx = floor(coord.x);
    int ly = floor(coord.y);

    float tu, tv;

    switch(bh) {
        case ImageTexture::CLAMP:
            tu = coord.x < 0 ? 0.0f : coord.x;
            tu = coord.x > 1 ? 1.0f : tu;
            tv = coord.y < 0 ? 0.0f : coord.y;
            tv = coord.y > 1 ? 1.0f : tv;
            break;

        case ImageTexture::MIRROR:
            tu = coord.x - lx;
            tv = coord.y - ly;
            if (abs(lx) % 2 == 1) {tu = 1 - tu;}
            if (abs(ly) % 2 == 1) {tv = 1 - tv;}
            break;

        case ImageTexture::REPEAT:
            tu = coord.x - lx;
            tv = coord.y - ly;
            break;
    }

    float resu = img.width();
    float resv = img.height();

    float u, v, iu, iv;

    switch(i) {
        case ImageTexture::NEAREST:
            u = tu * resu;
            v = tv * resv;

            iu = std::fmin(floor(u), resu - 1.0f);
            iv = std::fmin(floor(v), resv - 1.0f);

            return img(iu, iv);

        case ImageTexture::BILINEAR:
            u = tu * (resu - 1.0f);
            v = tv * (resv - 1.0f);

            iu = u - floor(u);
            iv = v - floor(v);

            float flru = floor(u);
            float flrv = floor(v);

            return (
                (1 - iu) * (1 - iv) * img(flru, flrv) +
                (1 - iu) * iv * img(flru, flrv + 1) +
                iu * (1 - iv) * img(flru + 1, flrv) +
                iu * iv * img(flru + 1, flrv + 1)
            );
    }
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    Point p1 = Point(coord.x + 0.5f / img.width(), coord.y, coord.z);
    Point p2 = Point(coord.x - 0.5f / img.width(), coord.y, coord.z);
    return getColor(p1) - getColor(p2);
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    Point p1 = Point(coord.x, coord.y + 0.5f / img.height() * 5, coord.z);
    Point p2 = Point(coord.x, coord.y - 0.5f / img.height() * 5, coord.z);
    return getColor(p1) - getColor(p2);
}
}