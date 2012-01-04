#include "StdAfx.h"
#include <d2d1.h>
#include <iostream>
#include <string>
#include "nx/logging/Logging.h"
#include "nx/color/SolidColor.h"
#include "SolidColorLexer.h"
#include "SolidColorParser.h"

#ifdef _DEBUG
#pragma comment(lib, "antlr3cd.lib")
#else
#pragma comment(lib, "antlr3c.lib")
#endif

nx::color::SolidColor::SolidColor( const wchar_t *desc )
{
    pANTLR3_UINT8 input_string = (pANTLR3_UINT8)desc;
    ANTLR3_UINT32 size = static_cast<ANTLR3_UINT32>(wcslen(desc) * 2);
    pANTLR3_INPUT_STREAM stream = antlr3StringStreamNew(
                                      input_string,
                                      ANTLR3_ENC_UTF16,
                                      size,
                                      (pANTLR3_UINT8)"SolidColor");

    pANTLR3_UINT8 fName;
    pANTLR3_COMMON_TOKEN_STREAM tstream;

    pSolidColorLexer lxr = SolidColorLexerNew(stream);
    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
    pSolidColorParser psr = SolidColorParserNew(tstream);
    nx::color::SolidColor *color = psr->solidColor(psr);
    if (psr->pParser->rec->state->errorCount > 0) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Failed to parse solid color descriptor '" << desc << L"'";
        throw std::invalid_argument("Failed to parse solid color descriptor");
    }
    m_color = color->m_color;
    delete color;
}

static void _RgbToHsv(IN float r, IN float g, IN float b, OUT float &h, OUT float &s, OUT float &v)
{
    float _max = v = std::max(std::max(r, g), b);
    float _min  = std::min(std::min(r, g), b);
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

DWORD nx::color::SolidColor::ToUIHsbColor() const
{
    float hue, saturation, brightness;
    _RgbToHsv(m_color.r, m_color.g, m_color.b, hue, saturation, brightness);
    DWORD c =
        static_cast<BYTE>(hue / 360.0 * 256.0) |
        static_cast<BYTE>(saturation / 100.0 * 256.0) << 8 |
        static_cast<BYTE>(brightness / 100.0 * 256.0);
    return c;
}
