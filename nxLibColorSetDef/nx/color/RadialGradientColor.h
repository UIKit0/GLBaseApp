#ifndef NX_COLOR_RADIALGRADIENTCOLOR_H_
#define NX_COLOR_RADIALGRADIENTCOLOR_H_

#include "nx/color/SolidColor.h"

namespace nx
{
namespace color
{
class RadialGradientColor
{
private:
    std::vector<D2D1_GRADIENT_STOP> m_gradientStops;
    D2D1_POINT_2F m_offsetRatio;

public:
    RadialGradientColor(void) :
        m_gradientStops(),
        m_offsetRatio(D2D1::Point2F())
    {}
    RadialGradientColor(std::vector<D2D1_GRADIENT_STOP>::size_type size) :
        m_gradientStops(size),
        m_offsetRatio(D2D1::Point2F())
    {}
    RadialGradientColor(const wchar_t *desc);
    RadialGradientColor(const RadialGradientColor& other) :
        m_gradientStops(other.m_gradientStops),
        m_offsetRatio(D2D1::Point2F())
    {}
    RadialGradientColor(RadialGradientColor && other) :
        m_gradientStops(std::move(other.m_gradientStops)),
        m_offsetRatio(other.m_offsetRatio)
    {}
    RadialGradientColor& operator=(const RadialGradientColor& other) {
        if (this != &other) {
            m_gradientStops = other.m_gradientStops;
            m_offsetRatio = other.m_offsetRatio;
        }
        return *this;
    }
    RadialGradientColor& operator=(RadialGradientColor && other) {
        if (this != &other) {
            m_gradientStops = std::move(other.m_gradientStops);
            m_offsetRatio = other.m_offsetRatio;
        }
        return *this;
    }
    bool operator==(const RadialGradientColor& other) const {
        return m_gradientStops.size() == other.m_gradientStops.size() &&
               std::equal(m_gradientStops.begin(), m_gradientStops.end(), other.m_gradientStops.begin(),
        [](const D2D1_GRADIENT_STOP & e1, const D2D1_GRADIENT_STOP & e2) {
            return e1.color.r == e2.color.r && e1.position == e2.position;
        }) && m_offsetRatio.x == other.m_offsetRatio.x &&
               m_offsetRatio.y == other.m_offsetRatio.y;
    }
    bool operator!=(const RadialGradientColor& other) const {
        return !(*this == other);
    }
    void SetOffsetRatio(FLOAT x, FLOAT y) {
        m_offsetRatio.x = x;
        m_offsetRatio.y = y;
    }
    void SetOffsetRatio(D2D1_POINT_2F offsetRatio) {
        m_offsetRatio = offsetRatio;
    }
    const D2D1_POINT_2F& GetOffsetRatio() const {
        return m_offsetRatio;
    }
    void AddGradientStop(FLOAT position, const D2D1_COLOR_F &color) {
        m_gradientStops.push_back(D2D1::GradientStop(position, color));
    }
    void AddGradientStop(FLOAT position, const SolidColor &color) {
        m_gradientStops.push_back(D2D1::GradientStop(position, color.ToD2DColor()));
    }
    void AddGradientStop(FLOAT position, FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) {
        m_gradientStops.push_back(D2D1::GradientStop(position, D2D1::ColorF(red, green, blue, alpha)));
    }
    const std::vector<D2D1_GRADIENT_STOP>& ToD2DGradientStops() const {
        return m_gradientStops;
    }
};
}
}

#endif // NX_COLOR_RADIALGRADIENTCOLOR_H_