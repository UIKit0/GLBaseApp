grammar SolidColor;

options
{
    language = C;
}

scope ColorSet {
	nx::color::SolidColor *solidColor;
}

@lexer::header
{
// @lexer::header
#define ANTLR3_INLINE_INPUT_UTF16

#include <d2d1.h>
#include <iostream>
#include "nx/color/SolidColor.h"
#include "nx/color/internal/Utils.h"
using namespace nx::color;
using namespace nx::color::internal;
}

@parser::includes
{
// @parser::includes
#include <d2d1.h>
#include <iostream>
#include "nx/color/SolidColor.h"
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

solidColor returns [nx::color::SolidColor* ret]
	scope ColorSet;
	@init {
		$ColorSet::solidColor = new nx::color::SolidColor();
	}
	:
	( rgba | hsba )
	{
		$ret = $ColorSet::solidColor;
	}
	;

rgba :	
	('rgba(' r=FLOAT ',' g=FLOAT ',' b=FLOAT ',' a=FLOAT ')')
	{
		$ColorSet::solidColor->SetColor(
			pu8tof($r.text->chars),
			pu8tof($g.text->chars),
			pu8tof($b.text->chars),
			pu8tof($a.text->chars));
	} | 
	('rgba(' rgb=HEXINT ',' a=FLOAT ')')
	{
		float red, green, blue;
		parse3values($rgb.text->chars, &red, &green, &blue);
		$ColorSet::solidColor->SetColor(
			red,
			green,
			blue,
			pu8tof($a.text->chars));
	}
	;
hsba :	
	'hsba(' h=FLOAT ',' s=FLOAT ',' b=FLOAT ',' a=FLOAT ')'
	{
		float red, green, blue;
		HsvToRgb(
			pu8tof($h.text->chars),
			pu8tof($s.text->chars),
			pu8tof($b.text->chars),
			red,
			green,
			blue);
		$ColorSet::solidColor->SetColor(
			red,
			green,
			blue,
			pu8tof($a.text->chars));
	}
	;
	