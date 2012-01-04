#include <d2d1.h>
#include <iostream>
#include <string>
#include <vector>
#include "nx/logging/Logging.h"
#include "nx/color/RadialGradientColor.h"
#include "RadialGradientColorLexer.h"
#include "RadialGradientColorParser.h"

nx::color::RadialGradientColor::RadialGradientColor( const wchar_t *desc )
{
    pANTLR3_UINT8 input_string = (pANTLR3_UINT8)desc;
    ANTLR3_UINT32 size = static_cast<ANTLR3_UINT32>(wcslen(desc) * 2);
    pANTLR3_INPUT_STREAM stream = antlr3StringStreamNew(
                                      input_string,
                                      ANTLR3_ENC_UTF16,
                                      size,
                                      (pANTLR3_UINT8)"RadialGradientColor");

    pANTLR3_UINT8 fName;
    pANTLR3_COMMON_TOKEN_STREAM tstream;

    pRadialGradientColorLexer lxr = RadialGradientColorLexerNew(stream);
    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
    pRadialGradientColorParser psr = RadialGradientColorParserNew(tstream);

    nx::color::RadialGradientColor *color = psr->radialColor(psr);
    if (psr->pParser->rec->state->errorCount > 0) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Failed to parse radial color descriptor '" << desc << L"'";
        throw std::invalid_argument("Failed to parse radial color descriptor");
    }
    m_offsetRatio = color->m_offsetRatio;
    m_gradientStops = std::move(color->m_gradientStops);
    delete color;
}
