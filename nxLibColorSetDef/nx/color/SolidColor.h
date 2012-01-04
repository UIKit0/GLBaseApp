#ifndef NX_COLOR_SOLIDCOLOR_H_
#define NX_COLOR_SOLIDCOLOR_H_

namespace nx
{
namespace color
{
class SolidColor
{
private:
    D2D1_COLOR_F m_color;

public:
    SolidColor(void) : m_color(D2D1::ColorF(0))
    {}
    SolidColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha = 1.0f) :
        m_color(D2D1::ColorF(red, green, blue, alpha))
    {}
    SolidColor(D2D1_COLOR_F color) : m_color(color)
    {}
    SolidColor(const wchar_t *desc);
    SolidColor(const SolidColor& solidColor) :
        m_color(solidColor.m_color)
    {}
    SolidColor& operator=(const SolidColor& other) {
        if (this != &other) {
            m_color = other.m_color;
        }
        return *this;
    }
    bool operator==(const SolidColor& other) const {
        return m_color.r == other.m_color.r &&
               m_color.g == other.m_color.g &&
               m_color.b == other.m_color.b &&
               m_color.a == other.m_color.a;
    }
    bool operator!=(const SolidColor& other) const {
        return !(*this == other);
    }
    const D2D1_COLOR_F& ToD2DColor() const {
        return m_color;
    }
    void SetColor(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha = 1.0f) {
        m_color = D2D1::ColorF(red, green, blue, alpha);
    }
    FLOAT GetRed() const {
        return m_color.r;
    }
    FLOAT GetGreen() const {
        return m_color.g;
    }
    FLOAT GetBlue() const {
        return m_color.b;
    }
    FLOAT GetAlpha() const {
        return m_color.a;
    }
    DWORD ToUIHsbColor() const;
};
inline std::wostream& operator<<(std::wostream& os, const SolidColor &solidColor)
{
    os << typeid(solidColor).name()
       << L"[r=" << solidColor.GetRed()
       << L",g=" << solidColor.GetGreen()
       << L",b=" << solidColor.GetBlue()
       << L",a=" << solidColor.GetAlpha()
       << L"]";
    return os;
}
}
}

#endif // NX_COLOR_SOLIDCOLOR_H_