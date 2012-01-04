del ColorSetDefLexer.cpp
del ColorSetDefParser.cpp
java -classpath C:\opt\antlr-3.3\lib\antlr-3.3-complete.jar org.antlr.Tool ColorSetDef.g
ren ColorSetDefLexer.c ColorSetDefLexer.cpp
ren ColorSetDefParser.c ColorSetDefParser.cpp

del SolidColorLexer.cpp
del SolidColorParser.cpp
java -classpath C:\opt\antlr-3.3\lib\antlr-3.3-complete.jar org.antlr.Tool SolidColor.g
ren SolidColorLexer.c SolidColorLexer.cpp
ren SolidColorParser.c SolidColorParser.cpp

del LinearGradientColorLexer.cpp
del LinearGradientColorParser.cpp
java -classpath C:\opt\antlr-3.3\lib\antlr-3.3-complete.jar org.antlr.Tool LinearGradientColor.g
ren LinearGradientColorLexer.c LinearGradientColorLexer.cpp
ren LinearGradientColorParser.c LinearGradientColorParser.cpp

del RadialGradientColorLexer.cpp
del RadialGradientColorParser.cpp
java -classpath C:\opt\antlr-3.3\lib\antlr-3.3-complete.jar org.antlr.Tool RadialGradientColor.g
ren RadialGradientColorLexer.c RadialGradientColorLexer.cpp
ren RadialGradientColorParser.c RadialGradientColorParser.cpp
