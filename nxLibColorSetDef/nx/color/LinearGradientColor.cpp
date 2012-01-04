#include <d2d1.h>
#include <iostream>
#include <string>
#include <vector>
#include "nx/logging/Logging.h"
#include "nx/color/LinearGradientColor.h"
#include "LinearGradientColorLexer.h"
#include "LinearGradientColorParser.h"

nx::color::LinearGradientColor::LinearGradientColor( const wchar_t *desc )
{
    pANTLR3_UINT8 input_string = (pANTLR3_UINT8)desc;
    ANTLR3_UINT32 size = static_cast<ANTLR3_UINT32>(wcslen(desc) * 2);
    pANTLR3_INPUT_STREAM stream = antlr3StringStreamNew(
                                      input_string,
                                      ANTLR3_ENC_UTF16,
                                      size,
                                      (pANTLR3_UINT8)"LinearGradientColor");

    pANTLR3_UINT8 fName;
    pANTLR3_COMMON_TOKEN_STREAM tstream;

    pLinearGradientColorLexer lxr = LinearGradientColorLexerNew(stream);
    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));
    pLinearGradientColorParser psr = LinearGradientColorParserNew(tstream);

    nx::color::LinearGradientColor *color = psr->linearColor(psr);
    if (psr->pParser->rec->state->errorCount > 0) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Failed to parse linear color descriptor '" << desc << L"'";
        throw std::invalid_argument("Failed to parse linear color descriptor");
    }
    m_gradientDirection = color->m_gradientDirection;
    m_gradientStops = std::move(color->m_gradientStops);
    delete color;
}
