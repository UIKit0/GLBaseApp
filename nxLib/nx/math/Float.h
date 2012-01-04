#ifndef NX_MATH_FLOAT_H_
#define NX_MATH_FLOAT_H_

namespace nx
{
namespace math
{

class Float
{
public:
    static float EPSILON;
    static bool AlmostEqual(float v1, float v2) {
        return std::abs(v1 - v2) <= EPSILON * (std::abs(v1) + std::abs(v2) + 1.0f);
    }
};

} // math
} // nx

#endif // NX_MATH_FLOAT_H_