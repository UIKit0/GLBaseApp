#pragma once

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Propsys.lib")
#pragma comment(lib, "Uxtheme.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "xpsprint.lib")
#pragma comment(lib, "Prntvpt.lib")
#pragma comment(lib, "Uiautomationcore.lib")

#ifdef _M_X64

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/AppLib.lib")
#pragma comment(lib, "../x64/Debug/nxLib.lib")
#pragma comment(lib, "../x64/Debug/nxLibColorSetDef.lib")
#else
#pragma comment(lib, "../x64/Release/AppLib.lib")
#pragma comment(lib, "../x64/Release/nxLib.lib")
#pragma comment(lib, "../x64/Release/nxLibColorSetDef.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment(lib, "../Debug/AppLib.lib")
#pragma comment(lib, "../Debug/nxLib.lib")
#pragma comment(lib, "../Debug/nxLibColorSetDef.lib")
#else
#pragma comment(lib, "../Release/AppLib.lib")
#pragma comment(lib, "../Release/nxLib.lib")
#pragma comment(lib, "../Release/nxLibColorSetDef.lib")
#endif

#if defined( DEBUG ) || defined( _DEBUG )
#pragma comment(lib, "glew32sd.lib")
#else
#pragma comment(lib, "glew32s.lib")
#endif
#pragma comment(lib, "opengl32.lib")

#endif
