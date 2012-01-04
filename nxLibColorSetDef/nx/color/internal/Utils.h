#ifndef NX_COLOR_INTERNAL_UTILS_H_
#define NX_COLOR_INTERNAL_UTILS_H_

#include <iostream>
#include <antlr3.h>

namespace nx
{
namespace color
{
namespace internal
{
inline float pu8tof(pANTLR3_UINT8 chars)
{
    return (float)_wtof((const wchar_t *)chars);
}
inline float getValue1(long value)
{
    return ((value & 0xff0000) >> 16) / 255.0f;
}

inline float getValue2(long value)
{
    return ((value & 0xff00) >> 8) / 255.0f;
}

inline float getValue3(long value)
{
    return (value & 0xff) / 255.0f;
}
extern void parse3values(pANTLR3_UINT8 _chars, float *value1, float *value2, float *value3);
extern void HsvToRgb(IN FLOAT h, IN FLOAT s, IN FLOAT v, OUT FLOAT &r, OUT FLOAT &g, OUT FLOAT &b);
}
}
}

#endif