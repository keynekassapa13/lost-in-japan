#include <rt/textures/perlin.h>
#include <core/point.h>
#include <vector>
#include <math.h>
#include <core/interpolate.h>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
{
    this->w = white;
    this->b = black;
}


rt::RGBColor PerlinTexture::getColor(const Point& coord) {
    float interpolation = 0.0f;
	for (int i = 0; i < f.size(); i++) {
		int f_lu = floorf(coord.x * f[i]);
		int f_lv = floorf(coord.y * f[i]);
		int f_lw = floorf(coord.z * f[i]);

		float frac_u = coord.x * f[i] - f_lu;
		float frac_v = coord.y * f[i] - f_lv;
		float frac_w = coord.z * f[i] - f_lw;

		interpolation = interpolation +
            lerp3d(
                noise(f_lu,     f_lv,       f_lw), 
                noise(f_lu + 1, f_lv,       f_lw), 
                noise(f_lu,     f_lv + 1,   f_lw),
                noise(f_lu + 1, f_lv + 1,   f_lw), 
                noise(f_lu,     f_lv,       f_lw + 1), 
                noise(f_lu + 1, f_lv,       f_lw + 1),
                noise(f_lu,     f_lv + 1,   f_lw + 1), 
                noise(f_lu + 1, f_lv + 1,   f_lw + 1),
                frac_u, 
                frac_v, 
                frac_w
            ) * a[i];
	}

	interpolation = (interpolation + 1) / 2;
	RGBColor color = lerp(b, w, interpolation);
	return color;
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    a.push_back(amplitude);
	f.push_back(frequency);
}

}