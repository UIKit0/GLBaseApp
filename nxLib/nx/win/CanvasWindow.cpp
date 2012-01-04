#include "stdafx.h"
#include "nx/nxLib.h"
#include "nx/animation/AnimationHelper.h"
#include "nx/core/GLContext.h"
#include "nx/win/MainWindow.h"
#include "nx/win/CanvasWindow.h"
#include "nx/ribbon/RibbonFramework.h"
#include "nx/touch/ManipulationHelper.h"
#include "nx/tsf/TSFManager.h"
#include "nx/util/OSVersionChecker.h"
#include "nx/util/Utils.h"

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_NX_WIN_CANVASWINDOW
#define DEBUG_NX_WIN_CANVASWINDOW_WINMSG
#endif

nx::win::CanvasWindow::CanvasWindow(void) :
    m_renderOnAnimationUpdated(false),
    m_enableHorizontalScrollbar(false),
    m_enableVerticalScrollbar(false),
    m_isInitialized(false),
    m_ribbonHeight(0),
    m_contextMenuViewId(0),
    m_enableContextMenu(false),
    m_hwnd(0),
    m_pContext(),
    m_manipulationHelper(new nx::touch::ManipulationHelper()),
    m_pMainWindow(),
    m_gestureConfig(5),
    m_animationHelper(new nx::animation::AnimationHelper())
{
    m_gestureConfig[0].dwID = GID_ZOOM;
    m_gestureConfig[0].dwWant = GC_ZOOM;
    m_gestureConfig[0].dwBlock = 0;
    m_gestureConfig[1].dwID = GID_PAN;
    m_gestureConfig[1].dwWant = GC_PAN_WITH_INERTIA;
    m_gestureConfig[1].dwBlock = 0;
    m_gestureConfig[2].dwID = GID_ROTATE;
    m_gestureConfig[2].dwWant = 0;
    m_gestureConfig[2].dwBlock = GC_ROTATE;
    m_gestureConfig[3].dwID = GID_TWOFINGERTAP;
    m_gestureConfig[3].dwWant = GC_TWOFINGERTAP;
    m_gestureConfig[3].dwBlock = 0;
    m_gestureConfig[4].dwID = GID_PRESSANDTAP;
    m_gestureConfig[4].dwWant = GC_PRESSANDTAP;
    m_gestureConfig[4].dwBlock = 0;
}

nx::win::CanvasWindow::~CanvasWindow(void)
{
}

void nx::win::CanvasWindow::Initialize()
{
    m_ribbonHeight = m_pMainWindow->GetRibbonHeight();

    WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
    wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc   = CanvasWindow::WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = sizeof(LONG_PTR);
    wcex.hInstance     = HINST_THISCOMPONENT;
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName  = nullptr;
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = L"CanvasWindow";
    RegisterClassEx(&wcex);

    HWND parentHwnd = m_pMainWindow->GetHWnd();
    RECT rc;
    ::GetClientRect(parentHwnd, &rc);
    rc.top = m_ribbonHeight;
    rc.bottom -= m_ribbonHeight;

    DWORD windowStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN;
    if (m_enableHorizontalScrollbar) {
        windowStyle |= WS_HSCROLL;
    }
    if (m_enableVerticalScrollbar) {
        windowStyle |= WS_VSCROLL;
    }

    m_hwnd = CreateWindow(
                 L"CanvasWindow",
                 L"CanvasWindow",
                 windowStyle,
                 rc.left, rc.top, rc.right, rc.bottom,
                 parentHwnd,
                 nullptr,
                 HINST_THISCOMPONENT,
                 this
             );
    if (m_hwnd != nullptr) {
        InitializeAfterCreate();
        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        UpdateWindow(m_hwnd);
    }
    m_isInitialized = true;
}

void nx::win::CanvasWindow::InitializeAfterCreate()
{
    m_pContext->SetHWnd(m_hwnd);
    m_pContext->Initialize();
    _SetGestureConfigs(m_hwnd);
    m_animationHelper->Initialize();
    ::SetFocus(m_hwnd);
}

void nx::win::CanvasWindow::OnCreate()
{
}

void nx::win::CanvasWindow::_SetGestureConfigs(HWND hWnd)
{
    if (!nx::util::OSVersionChecker::IsWin7()) {
        return;
    }
    UINT uiGcs = static_cast<UINT>(m_gestureConfig.size());
    BOOL bResult = ::SetGestureConfig(hWnd, 0, uiGcs, &m_gestureConfig.front(), sizeof(GESTURECONFIG));
    if (!bResult) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << nx::util::LastError(nx::util::LastErrorArgs(L"SetGestureConfig", lastError));
    }
}

LRESULT CALLBACK nx::win::CanvasWindow::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
#ifdef DEBUG_NX_WIN_CANVASWINDOW_WINMSG
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
    LOG(SEVERITY_LEVEL_DEBUG) << nx::util::WMessage(nx::util::WMessageArgs(hWnd, message, wParam, lParam));
#endif

    LRESULT result = 0;

    if (message == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT) lParam;
        CanvasWindow *pCanvasWindow = (CanvasWindow *) pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hWnd,
            GWLP_USERDATA,
            PtrToUlong(pCanvasWindow)
        );

        pCanvasWindow->OnCreate();
        result = 1;
    } else {
        nx::touch::ManipulationResult manipulationResult;
        CanvasWindow *pCanvasWindow = reinterpret_cast<CanvasWindow *>(static_cast<LONG_PTR>(
                                          ::GetWindowLongPtrW(
                                              hWnd,
                                              GWLP_USERDATA
                                          )));
        if (pCanvasWindow) {
            if (message == WM_LBUTTONDOWN && GetFocus() != pCanvasWindow->GetHWnd()) {
                // if mouse button down and the canvas panel has no focus, set focus to the canvas
                ::SetFocus(pCanvasWindow->GetHWnd());
            }
            manipulationResult = pCanvasWindow->m_manipulationHelper->WndProc(hWnd, message, wParam, lParam);
            switch (message) {
            case WM_ACTIVATE:
                if (WA_INACTIVE == LOWORD(wParam)) {
                    // do nothing
                    break;
                }
                // do SetFocus
            case WM_SETFOCUS:
                ::SetFocus(pCanvasWindow->m_hwnd);
                break;
            case WM_SIZE: {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                pCanvasWindow->OnResize(width, height);
            }
            manipulationResult.wasHandled = true;
            break;

            case WM_DISPLAYCHANGE:
            case WM_PAINT: {
                pCanvasWindow->OnRender();
            }
            manipulationResult.wasHandled = true;
            break;

            case WM_CONTEXTMENU: {
                pCanvasWindow->OnContextMenu(lParam);
            }
            manipulationResult.wasHandled = true;
            break;

            case WM_DESTROY: {
                PostQuitMessage(0);
                result = 1;
            }
            manipulationResult.wasHandled = true;
            break;
            }
        }

        if (!manipulationResult.wasHandled) {
            result = DefWindowProc(hWnd, message, wParam, lParam);
        }
        if (manipulationResult.requireInvalidateRect) {
            pCanvasWindow->Invalidate();
        }
    }

#ifdef DEBUG_NX_WIN_CANVASWINDOW_WINMSG
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return result;
}

void nx::win::CanvasWindow::ResizeByRibbonResized( UINT ribbonHeight )
{
    m_ribbonHeight = ribbonHeight;
    HWND parentHwnd = m_pMainWindow->GetHWnd();
    RECT rc;
    GetClientRect(parentHwnd, &rc);
    rc.top = ribbonHeight;
    rc.bottom -= ribbonHeight;
    MoveWindow(m_hwnd, rc.left, rc.top, rc.right, rc.bottom, TRUE);
}

void nx::win::CanvasWindow::Invalidate()
{
    InvalidateRect(m_hwnd, nullptr, TRUE);
}

void nx::win::CanvasWindow::OnResize( UINT width, UINT height )
{
    m_pContext->OnResize(width, height);
}

void nx::win::CanvasWindow::OnRender()
{
    HRESULT hr = S_OK;
    UI_ANIMATION_SECONDS secondsNow;
    hr = m_animationHelper->GetAnimationTimer()->GetTime(&secondsNow);
    if (SUCCEEDED(hr)) {
        hr = m_animationHelper->GetAnimationManager()->Update(secondsNow);
    }
    if (SUCCEEDED(hr)) {
        m_pContext->OnRender();
    }
    UI_ANIMATION_MANAGER_STATUS status;
    hr = m_animationHelper->GetAnimationManager()->GetStatus(&status);
    if (SUCCEEDED(hr) && m_renderOnAnimationUpdated && status == UI_ANIMATION_MANAGER_BUSY) {
        Invalidate();
    }
}

void nx::win::CanvasWindow::ResizeByParentResized()
{
    ResizeByRibbonResized(m_ribbonHeight);
}

void nx::win::CanvasWindow::OnContextMenu(LPARAM lParam)
{
    if (m_enableContextMenu) {
        POINT point;
        point.x = GET_X_LPARAM(lParam);
        point.y = GET_Y_LPARAM(lParam);
        m_pMainWindow->GetRibbonFramework()->ShowContextMenu(m_hwnd, point, m_contextMenuViewId);
    }
}

