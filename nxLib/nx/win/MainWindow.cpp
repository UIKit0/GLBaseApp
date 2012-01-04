#include "stdafx.h"
#include "nx/core/GLContext.h"
#include "nx/win/MainWindow.h"
#include "nx/tsf/TSFManager.h"
#include "nx/win/CanvasWindow.h"
#include "nx/ribbon/RibbonFramework.h"
#include "nx/ribbon/RibbonCommandHandler.h"
#include "nx/mui/MUI.h"
#include "nx/util/Utils.h"

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_NX_WIN_MAINWINDOW
#endif

nx::win::MainWindow::MainWindow(void) :
    m_hwnd(0),
    m_preferredWidth(1024),
    m_preferredHeight(768),
    m_title(L"Window Title"),
    m_pContext(new nx::core::GLContext()),
    m_ribbonFramework(new nx::ribbon::RibbonFramework()),
    m_canvasWindow(new nx::win::CanvasWindow())
{
}

nx::win::MainWindow::~MainWindow(void)
{
}

HRESULT nx::win::MainWindow::Initialize()
{
#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    m_canvasWindow->SetContext(m_pContext);
    m_canvasWindow->SetMainWindow(this);

    HICON hIcon = LoadIcon(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDI_APP));
    if (hIcon == nullptr) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << nx::util::LastError(nx::util::LastErrorArgs(L"LoadIcon", lastError));
        return E_FAIL;
    }

    HACCEL hAccel = LoadAccelerators(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDR_ACCELERATOR_DEFAULT));
    if (hAccel == nullptr) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << nx::util::LastError(nx::util::LastErrorArgs(L"LoadAccelerators", lastError));
        return E_FAIL;
    }

    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = nx::win::MainWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.hIcon = hIcon;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = L"MainWnd";

    RegisterClassEx(&wcex);

    HDC hdc = GetDC(nullptr);
    int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
    int dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
    ReleaseDC(nullptr, hdc);

    m_hwnd = CreateWindow(
                 L"MainWnd",
                 m_title.c_str(),
                 //L"TODO: Application Name", //nx::mui::MUI::GetString(IDS_APP_NAME),
                 WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                 CW_USEDEFAULT,
                 CW_USEDEFAULT,
                 static_cast<UINT>(std::ceil(m_preferredWidth * dpiX / 96.f)),
                 static_cast<UINT>(std::ceil(m_preferredHeight * dpiY / 96.f)),
                 nullptr,
                 nullptr,
                 HINST_THISCOMPONENT,
                 this);
    HRESULT hr = m_hwnd ? S_OK : E_FAIL;
    if (FAILED(hr)) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << nx::util::LastError(nx::util::LastErrorArgs(L"CreateWindow", lastError));
    } else {
        m_pTSFManager->SetAccelerator(m_hwnd, hAccel);
        m_pTSFManager->Initialize();
        m_ribbonFramework->Initialize(this);
        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        UpdateWindow(m_hwnd);
    }

#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return hr;
}

void nx::win::MainWindow::RunMessageLoop()
{
    m_pTSFManager->RunMessageLoop();
}

HRESULT nx::win::MainWindow::OnCreate( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(hwnd);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);
#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    m_canvasWindow->Initialize();

#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return S_OK;
}

LRESULT CALLBACK nx::win::MainWindow::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
    LOG(SEVERITY_LEVEL_DEBUG) << util::WMessage(util::WMessageArgs(hWnd, message, wParam, lParam));
#endif

    LRESULT result = 0;
    if (message == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT) lParam;
        nx::win::MainWindow *pMainWnd = (nx::win::MainWindow*) pcs->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToUlong(pMainWnd));
        result = 1;
    } else {
        nx::win::MainWindow *pMainWnd = reinterpret_cast<nx::win::MainWindow*>(
                                            static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
        bool wasHandled = false;

        if (pMainWnd) {
            switch (message) {
            case WM_COMMAND: {
                // Accelerator
                //switch (LOWORD(wParam)) {
                //case ID_ACCELERATOR_FPS:
                //    pMainWnd->SetFPSEnable(!pMainWnd->IsFPSEnabled());
                //}
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_SIZE:
                if (pMainWnd->m_canvasWindow.get() != nullptr
                        && pMainWnd->m_canvasWindow->IsInitialized()) {
                    pMainWnd->m_canvasWindow->ResizeByParentResized();
                }
                break;
            case WM_NCCREATE:
                result = 1;
                wasHandled = true;
                break;
            case WM_ACTIVATE:
                if (WA_INACTIVE == LOWORD(wParam)) {
                    // do nothing
                    break;
                }
                // do SetFocus
            case WM_SETFOCUS:
                ::SetFocus(pMainWnd->m_canvasWindow->GetHWnd());
                result = 1;
                wasHandled = true;
                break;
            case WM_RIBBON_RESIZED:
                if (pMainWnd->m_canvasWindow.get() != nullptr
                        && !pMainWnd->m_canvasWindow->IsInitialized()) {
                    pMainWnd->OnCreate(hWnd, message, wParam, lParam);
                } else if (pMainWnd->m_canvasWindow->IsInitialized()) {
                    pMainWnd->m_canvasWindow->ResizeByRibbonResized(static_cast < UINT >(wParam));
                }
                result = 0;
                wasHandled = true;
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                result = 1;
                wasHandled = true;
                break;/*
            case WM_GETOBJECT: {
                // Register the control with UI Automation.
                // If the lParam matches the RootObjectId, send back the list provider.
                if (static_cast<long>(lParam) == static_cast<long>(UiaRootObjectId)) {
                    // Get the control.
                    // Return its associated UI Automation provider.
                    IRawElementProviderSimple *pProvider = pMainWnd->GetCanvasWindow()->GetUIRoot()->GetUIRootProvider();
                    result = UiaReturnRawElementProvider(
                                 hWnd, wParam, lParam, pProvider);
                    wasHandled = true;
                } else {
                    result = 0;
                    wasHandled = false;
                }
            }*/
            }
        }
        if (!wasHandled) {
            result = DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

#ifdef DEBUG_NX_WIN_MAINWINDOW
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return result;
}

UINT nx::win::MainWindow::GetRibbonHeight() const
{
    return m_ribbonFramework->GetRibbonCommandHandler()->GetRibbonHeight();
}
