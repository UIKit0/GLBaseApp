grammar ColorSetDef;

options
{
    language = C;
}

scope ColorSet {
	nx::color::colorsetdef::COLORVALUE_TYPE colorValueType;
	float value1;
	float value2;
	float value3;
	float value4;
	float position;

	nx::color::colorsetdef::ColorSetDO* pColorSet;
}

@lexer::header
{
// @lexer::header
#define ANTLR3_INLINE_INPUT_UTF16

#include "nx/color/colorsetdef/ColorSetDef.h"
using namespace nx::color;
}

@parser::includes
{
// @parser::includes
#include "nx/color/colorsetdef/ColorSetDef.h"
using namespace nx::color;

inline float pu8tof(pANTLR3_UINT8 chars)
{
	return (float)_wtof((const wchar_t *)chars);
}

inline std::wstring trimSingleQuote(const std::wstring &s)
{
    size_t start = 0;
    size_t len = s.size();
    if (s.front() == L'\'') {
        start = 1;
        len--;
    }
    if (s.back() ==  L'\'') {
        len--;
    }
    return s.substr(start, len);
}

inline float getValue1(long value) {
	return ((value & 0xff0000) >> 16) / 255.0f;
}

inline float getValue2(long value) {
	return ((value & 0xff00) >> 8) / 255.0f;
}

inline float getValue3(long value) {
	return (value & 0xff) / 255.0f;
}

inline void parse3values(pANTLR3_UINT8 _chars, float *value1, float *value2, float *value3)
{
	wchar_t *chars = (wchar_t*)_chars;
	wchar_t *offset;
	
	size_t len = wcslen(chars);
	if(len > 2) {
		if(chars[0] == L'0' && chars[1] == L'x') {
			long ret = wcstol(chars, &offset, 0);
			*value1 = getValue1(ret);
			*value2 = getValue2(ret);
			*value3 = getValue3(ret);
			return;
		}
	}
	if(len > 1) {
		if(chars[0] == L'#') {
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

}

@declarations
{
  // declarations;
}

@init
{
  // init;
}

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :	'0'..'9'+
    ;

HEXINT 	:	('0x' | '#') HEX_DIGIT+;

FLOAT
    :   '-'? ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '-'? '.' ('0'..'9')+ EXPONENT?
    |   '-'? ('0'..'9')+ EXPONENT?
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;

STRING
    :  '\'' ( ESC_SEQ | ~('\\'|'\'') )* '\''
    ;

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;

colorSetDef returns [nx::color::colorsetdef::ColorSetDO* ret]
 	scope ColorSet;
	@init {
		$ColorSet::pColorSet = new nx::color::colorsetdef::ColorSetDO();
	}
	@after {
	}
	:
	colorDef (',' colorDef)* 
	{
		$ret = $ColorSet::pColorSet;
	}
	;
	
colorDef :
	solidColor | linearColor | radialColor;

solidColor
	@init {
		std::shared_ptr<colorsetdef::SolidColorDO> solidColor = 
			std::make_shared<colorsetdef::SolidColorDO>();
			$ColorSet::pColorSet->colors.push_back(solidColor);
	}
	:
	'solid' ('[' label=ID ']')? '(' ( rgba | hsba ) ')'
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_SOLID) {
			std::shared_ptr<colorsetdef::SolidColorDO> solidColor = 
				std::dynamic_pointer_cast<colorsetdef::SolidColorDO>
				($ColorSet::pColorSet->colors.back());
			if($label != NULL) {
				solidColor->label = trimSingleQuote((wchar_t*)$label.text->chars);
			}
			solidColor->colorValue = colorsetdef::ColorValueDO($ColorSet::colorValueType,
				$ColorSet::value1,
				$ColorSet::value2,
				$ColorSet::value3,
				$ColorSet::value4);
		}
	}
	;

linearColor	
	@init {
		std::shared_ptr<colorsetdef::LinearColorDO> linearColor = 
			std::make_shared<colorsetdef::LinearColorDO>();
			$ColorSet::pColorSet->colors.push_back(linearColor);
	}
	:
	'linear' ('[' label=ID ']')? '(' linearColorDirection ',' linerColorElement (',' linerColorElement)+ ')'
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_LINEAR) {
			std::shared_ptr<colorsetdef::LinearColorDO> linearColor = 
				std::dynamic_pointer_cast<colorsetdef::LinearColorDO>
				($ColorSet::pColorSet->colors.back());
			if($label != NULL) {
				linearColor->label = trimSingleQuote((wchar_t*)$label.text->chars);
			}
		}
	}
	;

linearColorDirection
	:	direction=('TOP_BOTTOM' | 'TOPLEFT_BOTTOMRIGHT')
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_LINEAR) {
			std::shared_ptr<colorsetdef::LinearColorDO> linearColor = 
				std::dynamic_pointer_cast<colorsetdef::LinearColorDO>
				($ColorSet::pColorSet->colors.back());
			if(wcscmp((wchar_t*)$direction.text->chars, L"TOP_BOTTOM") == 0) {
				linearColor->direction = colorsetdef::LinearColorDO::DIRECTION_TOP_BOTTOM;
			}
			else if(wcscmp((wchar_t*)$direction.text->chars, L"TOPLEFT_BOTTOMRIGHT") == 0) {
				linearColor->direction = colorsetdef::LinearColorDO::DIRECTION_TOPLEFT_BOTTOMRIGHT;
			}
		}
	}
	;

linerColorElement :
	( rgba | hsba ) '@' pos
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_LINEAR) {
			std::shared_ptr<colorsetdef::LinearColorDO> linearColor = 
				std::dynamic_pointer_cast<colorsetdef::LinearColorDO>
				($ColorSet::pColorSet->colors.back());
			colorsetdef::ColorValueDO colorValue(
									$ColorSet::colorValueType, 
									$ColorSet::value1, 
									$ColorSet::value2, 
									$ColorSet::value3, 
									$ColorSet::value4,
									$ColorSet::position);
			linearColor->colorValues.push_back(colorValue);
		}
	};	

radialColor
	@init {
		std::shared_ptr<colorsetdef::RadialColorDO> radialColor = 
			std::make_shared<colorsetdef::RadialColorDO>();
			$ColorSet::pColorSet->colors.push_back(radialColor);
	} 
	:
	'radial' ('[' label=ID ']')? '(' offsetX=FLOAT ',' offsetY=FLOAT ',' radialColorElement (',' radialColorElement)+ ')'
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_RADIAL) {
			std::shared_ptr<colorsetdef::RadialColorDO> radialColor = 
				std::dynamic_pointer_cast<colorsetdef::RadialColorDO>
				($ColorSet::pColorSet->colors.back());
			if($label != NULL) {
				radialColor->label = trimSingleQuote((wchar_t*)$label.text->chars);
			}
			radialColor->offsetX = pu8tof($offsetX.text->chars);
			radialColor->offsetY = pu8tof($offsetY.text->chars);
		}
	}
	;

radialColorElement :
	( rgba | hsba ) '@' pos
	{
		if($ColorSet::pColorSet->colors.back()->GetColorType() == colorsetdef::COLOR_TYPE_RADIAL) {
			std::shared_ptr<colorsetdef::RadialColorDO> radialColor = 
				std::dynamic_pointer_cast<colorsetdef::RadialColorDO>
				($ColorSet::pColorSet->colors.back());
			colorsetdef::ColorValueDO colorValue(
				$ColorSet::colorValueType, 
				$ColorSet::value1, 
				$ColorSet::value2, 
				$ColorSet::value3, 
				$ColorSet::value4,
				$ColorSet::position
				);
			radialColor->colorValues.push_back(colorValue);
		}
	};	

rgba :	
	('rgba(' r=FLOAT ',' g=FLOAT ',' b=FLOAT ',' a=FLOAT ')')
	{
		$ColorSet::colorValueType = colorsetdef::COLORVALUE_TYPE_RGBA;
		$ColorSet::value1 = pu8tof($r.text->chars);
		$ColorSet::value2 = pu8tof($g.text->chars);
		$ColorSet::value3 = pu8tof($b.text->chars);
		$ColorSet::value4 = pu8tof($a.text->chars);
	} | 
	('rgba(' rgb=HEXINT ',' a=FLOAT ')')
	{
		$ColorSet::colorValueType = colorsetdef::COLORVALUE_TYPE_RGBA;
		float value1, value2, value3;
		parse3values($rgb.text->chars, &value1, &value2, &value3);
		$ColorSet::value1 = value1;
		$ColorSet::value2 = value2;
		$ColorSet::value3 = value3;
		$ColorSet::value4 = pu8tof($a.text->chars);
	}
	;
hsba :	
	'hsba(' h=FLOAT ',' s=FLOAT ',' b=FLOAT ',' a=FLOAT ')'
	{
		$ColorSet::colorValueType = colorsetdef::COLORVALUE_TYPE_HSBA;
		$ColorSet::value1 = pu8tof($h.text->chars);
		$ColorSet::value2 = pu8tof($s.text->chars);
		$ColorSet::value3 = pu8tof($b.text->chars);
		$ColorSet::value4 = pu8tof($a.text->chars);
	}
	;

pos : value=FLOAT 
	{
		$ColorSet::position = pu8tof($value.text->chars);
	}
	;
	