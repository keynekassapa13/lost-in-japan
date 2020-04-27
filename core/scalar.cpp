#include <cmath>

namespace rt {

float fractional( float f ) {
    float intpart;
    return modff(f, &intpart);
}

float absfractional(float f) {
    float fr = fractional(f);
    if (fr>=0) return fr;
    fr += 1.0f;
    if (fr >= 1.0f) //can happed due to epsilon errors
        return 0.0f;
    return fr;
}

}
