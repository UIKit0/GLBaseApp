grammar RadialGradientColor;

options
{
    language = C;
}

scope ColorSet {
	float offsetRatioX;
	float offsetRatioY;
	float red;
	float green;
	float blue;
	float alpha;
	float position;
	
	nx::color::RadialGradientColor *color;
}

@lexer::header
{
// @lexer::header
#define ANTLR3_INLINE_INPUT_UTF16

#include <d2d1.h>
#include <iostream>
#include <vector>
#include "nx/color/RadialGradientColor.h"
#include "nx/color/internal/Utils.h"
using namespace nx::color;
using namespace nx::color::internal;
}

@parser::includes
{
// @parser::includes
#include <d2d1.h>
#include <iostream>
#include <vector>
#include "nx/color/RadialGradientColor.h"
#include "nx/color/internal/Utils.h"
using namespace nx::color;
using namespace nx::color::internal;
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

//INT :	'0'..'9'+
//    ;

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

radialColor returns [nx::color::RadialGradientColor* ret]
 	scope ColorSet;
	@init {
		$ColorSet::color = new nx::color::RadialGradientColor();
	} 
	:
	offsetX=FLOAT ',' offsetY=FLOAT ':' radialColorElement ('-' radialColorElement)+
	{
		$ColorSet::color->SetOffsetRatio(pu8tof($offsetX.text->chars), pu8tof($offsetY.text->chars));
		$ret = $ColorSet::color;
	}
	;

radialColorElement :
	( rgba | hsba ) '@' pos
	{
		$ColorSet::color->AddGradientStop($ColorSet::position, $ColorSet::red, $ColorSet::green, $ColorSet::blue, $ColorSet::alpha);
	};	

rgba :	
	('rgba(' r=FLOAT ',' g=FLOAT ',' b=FLOAT ',' a=FLOAT ')')
	{
		$ColorSet::red = pu8tof($r.text->chars);
		$ColorSet::green = pu8tof($g.text->chars);
		$ColorSet::blue = pu8tof($b.text->chars);
		$ColorSet::alpha = pu8tof($a.text->chars);
	} | 
	('rgba(' rgb=HEXINT ',' a=FLOAT ')')
	{
		parse3values($rgb.text->chars, &($ColorSet::red), &($ColorSet::green), &($ColorSet::blue));
		$ColorSet::alpha = pu8tof($a.text->chars);
	}
	;
hsba :	
	'hsba(' h=FLOAT ',' s=FLOAT ',' b=FLOAT ',' a=FLOAT ')'
	{
		HsvToRgb(
			pu8tof($h.text->chars),
			pu8tof($s.text->chars),
			pu8tof($b.text->chars),
			$ColorSet::red,
			$ColorSet::green,
			$ColorSet::blue);
		$ColorSet::alpha = pu8tof($a.text->chars);
	}
	;

pos : value=FLOAT 
	{
		$ColorSet::position = pu8tof($value.text->chars);
	}
	;
	