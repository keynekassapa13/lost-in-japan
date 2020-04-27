#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

	RGBColor::RGBColor(const Float4& f4)
	{
	/* TODO */ NOT_IMPLEMENTED;
	}

	RGBColor RGBColor::operator + (const RGBColor& c) const {
		return RGBColor(this->r + c.r, this->g + c.g, this->b + c.b);
	}

	RGBColor RGBColor::operator - (const RGBColor& c) const {
		return RGBColor(this->r - c.r, this->g - c.g, this->b - c.b);
	}

	RGBColor RGBColor::operator * (const RGBColor& c) const {
		return RGBColor(this->r * c.r, this->g * c.g, this->b * c.b);
	}

	bool RGBColor::operator == (const RGBColor& c) const {
		return this->r == c.r && this->g == c.g && this->b == c.b;
	}

	bool RGBColor::operator != (const RGBColor& b) const {
		return this->r != b.r || this->g != b.g || this->b != b.b;
	}

	RGBColor RGBColor::clamp() const {
		float cl_r = std::fmax(std::fmin(this->r, 1), 0);
		float cl_g = std::fmax(std::fmin(this->g, 1), 0);
		float cl_b = std::fmax(std::fmin(this->b, 1), 0);
		return RGBColor(cl_r, cl_g, cl_b);
	}

	RGBColor RGBColor::gamma(float gam) const {
		return RGBColor(powf(r, gam), powf(g, gam), powf(b, gam));
	}

	float RGBColor::luminance() const {
		return 0.2126f * r + 0.7152f * g + 0.0722f * b;
	}

	RGBColor operator * (float scalar, const RGBColor& c) {
		return RGBColor(c.r * scalar, c.g * scalar, c.b * scalar);
	}

	RGBColor operator * (const RGBColor& c, float scalar) {
		return scalar * c;
	}

	RGBColor operator / (const RGBColor& c, float scalar) {
		return RGBColor(c.r / scalar, c.g / scalar, c.b / scalar);
	}

}
