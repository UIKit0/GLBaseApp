#ifndef NX_COLOR_LINEARGRADIENTCOLOR_H_
#define NX_COLOR_LINEARGRADIENTCOLOR_H_

#include "nx/color/GradientDirection.h"
#include "nx/color/SolidColor.h"

namespace nx
{
namespace color
{
class LinearGradientColor
{
private:
    std::vector<D2D1_GRADIENT_STOP> m_gradientStops;
    GRADIENT_DIRECTION m_gradientDirection;

public:
    LinearGradientColor(void) :
        m_gradientStops(),
        m_gradientDirection(GRADIENT_DIRECTION_TOP_BOTTOM)
    {}
    LinearGradientColor(std::vector<D2D1_GRADIENT_STOP>::size_type size) :
        m_gradientStops(size),
        m_gradientDirection(GRADIENT_DIRECTION_TOP_BOTTOM)
    {}
    LinearGradientColor(const wchar_t *desc);
    LinearGradientColor(const LinearGradientColor& other) :
        m_gradientStops(other.m_gradientStops),
        m_gradientDirection(other.m_gradientDirection)
    {}
    LinearGradientColor(LinearGradientColor && other) :
        m_gradientStops(std::move(other.m_gradientStops)),
        m_gradientDirection(other.m_gradientDirection)
    {}
    LinearGradientColor& operator=(const LinearGradientColor& other) {
        if (this != &other) {
            m_gradientStops = other.m_gradientStops;
            m_gradientDirection = other.m_gradientDirection;
        }
        return *this;
    }
    LinearGradientColor& operator=(LinearGradientColor && other) {
        if (this != &other) {
            m_gradientStops = std::move(other.m_gradientStops);
            m_gradientDirection = other.m_gradientDirection;
        }
        return *this;
    }
    bool operator==(const LinearGradientColor& other) const {
        return m_gradientStops.size() == other.m_gradientStops.size() &&
               std::equal(m_gradientStops.begin(), m_gradientStops.end(), other.m_gradientStops.begin(),
        [](const D2D1_GRADIENT_STOP & e1, const D2D1_GRADIENT_STOP & e2) {
            return e1.color.r == e2.color.r && e1.position == e2.position;
        }) && m_gradientDirection == other.m_gradientDirection;
    }
    bool operator!=(const LinearGradientColor& other) const {
        return !(*this == other);
    }
    void SetGradientDirection(GRADIENT_DIRECTION gradientDirection) {
        m_gradientDirection = gradientDirection;
    }
    GRADIENT_DIRECTION GetGradientDirection() const {
        return m_gradientDirection;
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

#endif // NX_COLOR_LINEARGRADIENTCOLOR_H_