#include "stdafx.h"
#include "Common.h"
#include "Main.h"
#include "Renderer.h"
#include "nx/core/NXApplication.h"
#include "nx/core/GLContext.h"
#include "nx/event/IGLRenderEventListener.h"
#include "nx/ribbon/RibbonFramework.h"
#include "nx/win/MainWindow.h"
#include "nx/win/CanvasWindow.h"
#include "nx/tsf/TSFManager.h"

#include "Libs.h"

class CDummyModule : public CAtlExeModuleT<CDummyModule> {};
CDummyModule _Module;

int APIENTRY wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

    srand(static_cast<unsigned>(time(nullptr)));

    nx::core::NXApplication nxApp(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    nxApp.SetLogFilePath(L"GLAppBase\\GLAppBase.log");
    nxApp.SetMUIDllName(L"AppMUI.dll");
    nxApp.GetMainWindow()->SetPreferredSize(800, 600);
    nxApp.GetMainWindow()->SetTitle(L"GLAppBase");
    nxApp.GetMainWindow()->GetRibbonFramework()->SetColor(
        nx::color::SolidColor(L"hsba(35.0, 0.0, 0.3, 1.0)"),
        nx::color::SolidColor(L"hsba(360.0, 1.0, 1.0, 1.0)"),
        nx::color::SolidColor(L"hsba(360.0, 0.0, 1.0, 1.0)"));
    nxApp.GetMainWindow()->GetRibbonFramework()->AddExecuteFunctor(cmdExit,
            [&](UI_EXECUTIONVERB verb,
                const PROPERTYKEY * key,
                const PROPVARIANT * currentValue,
    IUISimplePropertySet * commandExecutionProperties)->HRESULT {
        UNREFERENCED_PARAMETER(verb);
        UNREFERENCED_PARAMETER(key);
        UNREFERENCED_PARAMETER(currentValue);
        UNREFERENCED_PARAMETER(commandExecutionProperties);
        ::PostMessage(nxApp.GetMainWindow()->GetHWnd(), WM_CLOSE, 0, 0);
        return S_OK;
    });

    Renderer renderer;
    nxApp.GetContext()->SetRenderEventListener(&renderer);

    //nxApp.GetMainWindow()->GetCanvasWindow()->SetEnableHorizontalScrollbar(true);
    //nxApp.GetMainWindow()->GetCanvasWindow()->SetEnableVerticalScrollbar(true);
    if (SUCCEEDED(nxApp.Initialize())) {
        nxApp.RunMessageLoop();
    }

    return 0;
}
