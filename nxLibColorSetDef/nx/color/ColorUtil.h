#ifndef NX_GFX_COLORUTIL_H_
#define NX_GFX_COLORUTIL_H_

namespace nx
{
namespace color
{
/**
 * カラーユーティリティ.
 */
class ColorUtil
{
private:
    ColorUtil(void) {}
    ~ColorUtil(void) {}
public:
    /**
     * COLORREF(GDI)からD2D1_COLOR_F(Direct2D)への変換.
     * @param[in] colorref COLORREF
     * @return D2D1_COLOR_F
     */
    static D2D1_COLOR_F ColorrefToColorF(const COLORREF &colorref) {
        return D2D1::ColorF(
                   GetRValue(colorref) / 255.0f,
                   GetGValue(colorref) / 255.0f,
                   GetBValue(colorref) / 255.0f, 1.0f);
    }
    /**
     * D2D1_COLOR_F(Direct2D)からCOLORREF(GDI)への変換.
     * @param[in] colorF D2D1_COLOR_F
     * @return COLORREF
     */
    static COLORREF ColorFToColorref(const D2D1_COLOR_F &colorF) {
        return RGB(colorF.r * 255, colorF.g * 255, colorF.b * 255);
    }
    /**
     * RGBからHSVへの変換.
     * @param[in] r Red値
     * @param[in] g Green値
     * @param[in] b Blue値
     * @param[out] h Hue値
     * @param[out] s Saturation値
     * @param[out] v Value値(=Brightness)
     */
    static void RgbToHsv(IN FLOAT r, IN FLOAT g, IN FLOAT b, OUT FLOAT &h, OUT FLOAT &s, OUT FLOAT &v) {
        FLOAT _max = v = std::max(std::max(r, g), b);
        FLOAT _min  = std::min(std::min(r, g), b);
        s = _max != 0.0f ?
            ( _max - _min ) / _max :
            0.0f; // if _max == 0.0f, s is undefined.
        if (_max == r) {
            h = (_max - _min != 0.0f) ?
                60.0f * (g - b) / (_max - _min) :
                0.0f; // if _max == _min, h is undefined.
        } else if (_max == g) {
            h = (_max - _min != 0.0f) ?
                60.0f * (b - r) / (_max - _min) + 120.0f :
                0.0f;
        } else {
            h = (_max - _min != 0.0f) ?
                60.0f * (r - g) / (_max - _min) + 240.0f :
                0.0f;
        }
        if (h < 0.0f) {
            h += 360.0f;
        }
    }
    /**
     * HSVからRGBへの変換.
     * @param[in] h Hue値
     * @param[in] s Saturation値
     * @param[in] v Value値(=Brightness)
     * @param[out] r Red値
     * @param[out] g Green値
     * @param[out] b Blue値
     */
    static void HsvToRgb(IN FLOAT h, IN FLOAT s, IN FLOAT v, OUT FLOAT &r, OUT FLOAT &g, OUT FLOAT &b) {
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
    /**
     * HSVからRGB(D2D1_COLOR_F)への変換.
     * @param[in] h Hue値
     * @param[in] s Saturation値
     * @param[in] v Value値(=Brightness)
     * @param[in] a アルファ値
     * @return D2D1_COLOR_F
     */
    static D2D1_COLOR_F HsvToRgb(FLOAT h, FLOAT s, FLOAT v, FLOAT a) {
        D2D1_COLOR_F c;
        HsvToRgb(h, s, v, c.r, c.g, c.b);
        c.a = a;
        return c;
    }
    /**
     * 飽和.
     * @param[in] value 値
     * @param[in] limit リミット値
     * @return リミットまでに丸められた値
     */
    static FLOAT Saturate(FLOAT value, FLOAT limit) {
        return value > limit ? limit : value;
    }

};
}
}

#endif // GRAPHICS_COLORUTIL_H_
