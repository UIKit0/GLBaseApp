#include "nx/color/internal/Utils.h"

namespace nx
{
namespace color
{
namespace internal
{
void parse3values(pANTLR3_UINT8 _chars, float *value1, float *value2, float *value3)
{
    wchar_t *chars = (wchar_t*)_chars;
    wchar_t *offset;

    size_t len = wcslen(chars);
    if (len > 2) {
        if (chars[0] == L'0' && chars[1] == L'x') {
            long ret = wcstol(chars, &offset, 0);
            *value1 = getValue1(ret);
            *value2 = getValue2(ret);
            *value3 = getValue3(ret);
            return;
        }
    }
    if (len > 1) {
        if (chars[0] == L'#') {
            long ret = wcstol(chars + 1, &offset, 16);
            *value1 = getValue1(ret);
            *value2 = getValue2(ret);
            *value3 = getValue3(ret);
            return;
        }
    }
    long ret = wcstol(chars, &offset, 16);
    *value1 = getValue1(ret);
    *value2 = getValue2(ret);
    *value3 = getValue3(ret);
}

void HsvToRgb(IN FLOAT h, IN FLOAT s, IN FLOAT v, OUT FLOAT &r, OUT FLOAT &g, OUT FLOAT &b)
{
    int hi = static_cast<int>( h / 60.0f ) % 6;
    FLOAT f = ( h / 60.0f ) - hi;
    FLOAT p = v * (1.0f - s);
    FLOAT q = v * (1.0f - f * s);
    FLOAT t = v * (1.0f - (1.0f - f) * s);
    switch ( hi ) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
}

}
}
}