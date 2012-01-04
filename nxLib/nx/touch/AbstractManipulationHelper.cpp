#include "StdAfx.h"
#include "nx/touch/AbstractManipulationHelper.h"
#include "nx/util/Utils.h"

UINT_PTR nx::touch::AbstractManipulationHelper::s_masterTimerId = 1;

nx::touch::AbstractManipulationHelper::AbstractManipulationHelper(void) :
    m_draggingStatus(DRAGGING_STATUS_NOT_DRAGGING),
    m_timerIdForDoubleClick(s_masterTimerId++),
    m_hCursor(nullptr),
    m_mouseCursorType(MOUSE_CURSOR_TYPE_DEFAULT)
{
    m_lastPoint.x = -1;
    m_lastPoint.y = -1;
}

nx::touch::AbstractManipulationHelper::~AbstractManipulationHelper(void)
{
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnLeftMouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    m_draggingStatus = DRAGGING_STATUS_PREPARE;
    m_lastPoint.x = GET_X_LPARAM(lParam);
    m_lastPoint.y = GET_Y_LPARAM(lParam);
    ::SetCapture(hWnd);

    POINT windowPoint;
    windowPoint.x = GET_X_LPARAM(lParam);
    windowPoint.y = GET_Y_LPARAM(lParam);
    return OnLeftMouseDownExt(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnMouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    bool leftButtonDown = (wParam & MK_LBUTTON) != 0;

    nx::touch::ManipulationResult result;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    if (leftButtonDown && m_draggingStatus == DRAGGING_STATUS_PREPARE) {
        // start mouse dragging
        m_dragRect.left = m_lastPoint.x;
        m_dragRect.top = m_lastPoint.y;
        m_dragRect.right = GET_X_LPARAM(lParam);
        m_dragRect.bottom = GET_Y_LPARAM(lParam);
        LONG dx = 0;
        LONG dy = 0;
        if (m_lastPoint.x != -1 && m_lastPoint.y != -1) {
            dx = m_dragRect.right - m_lastPoint.x;
            dy = m_dragRect.bottom - m_lastPoint.y;
        }
        result = OnDraggingStart(m_pContext, hWnd, wParam, lParam, m_dragRect, dx, dy, currentTimestampInMilliSeconds);
        ::SetCapture(hWnd);
        m_draggingStatus = DRAGGING_STATUS_DRAGGING;
    } else if (leftButtonDown && m_draggingStatus == DRAGGING_STATUS_DRAGGING) {
        // Mouse dragging
        m_dragRect.right = GET_X_LPARAM(lParam);
        m_dragRect.bottom = GET_Y_LPARAM(lParam);
        LONG dx = 0;
        LONG dy = 0;
        if (m_lastPoint.x != -1 && m_lastPoint.y != -1) {
            dx = m_dragRect.right - m_lastPoint.x;
            dy = m_dragRect.bottom - m_lastPoint.y;
        }
        result = OnDragging(m_pContext, hWnd, wParam, lParam, m_dragRect, dx, dy, currentTimestampInMilliSeconds);
        ::SetCapture(hWnd);
    } else if (!leftButtonDown && m_draggingStatus == DRAGGING_STATUS_DRAGGING) {
        // mouse left button up but WM_LBUTTONUP event has not been received.
        // usually this situation does not happen
        m_dragRect.right = GET_X_LPARAM(lParam);
        m_dragRect.bottom = GET_Y_LPARAM(lParam);
        LONG dx = 0;
        LONG dy = 0;
        if (m_lastPoint.x != -1 && m_lastPoint.y != -1) {
            dx = m_dragRect.right - m_lastPoint.x;
            dy = m_dragRect.bottom - m_lastPoint.y;
        }
        result = OnDraggingEnd(m_pContext, hWnd, wParam, lParam, m_dragRect, dx, dy, currentTimestampInMilliSeconds);
        ::ReleaseCapture();
        m_draggingStatus = DRAGGING_STATUS_NOT_DRAGGING;
    } else {
        // Mouse move
        POINT windowPoint;
        windowPoint.x = GET_X_LPARAM(lParam);
        windowPoint.y = GET_Y_LPARAM(lParam);
        LONG dx = 0;
        LONG dy = 0;
        if (m_lastPoint.x != -1 && m_lastPoint.y != -1) {
            dx = windowPoint.x - m_lastPoint.x;
            dy = windowPoint.y - m_lastPoint.y;
        }
        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (0 <= windowPoint.x && windowPoint.x <= width &&
                0 <= windowPoint.y && windowPoint.y <= height) {
            result = OnMouseOver(m_pContext, hWnd, wParam, lParam, windowPoint, dx, dy, currentTimestampInMilliSeconds);
            ::SetCapture(hWnd);
        } else {
            result = OnMouseOut(m_pContext, hWnd, wParam, lParam, windowPoint, dx, dy, currentTimestampInMilliSeconds);
            ::ReleaseCapture();
        }
        m_draggingStatus = DRAGGING_STATUS_NOT_DRAGGING;
    }
    m_lastPoint.x = GET_X_LPARAM(lParam);
    m_lastPoint.y = GET_Y_LPARAM(lParam);

    return result;
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnLeftMouseDoubleClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    m_draggingStatus = DRAGGING_STATUS_NOT_DRAGGING;
    // Left mouse button double click
    if (! ::KillTimer(hWnd, m_timerIdForDoubleClick)) {
        DWORD lastError = GetLastError();
        LOG(SEVERITY_LEVEL_ERROR) << util::LastError(util::LastErrorArgs(L"KillTimer", lastError));
        ManipulationResult result(false, false);
        return result;
    }
    POINT windowPoint;
    windowPoint.x = GET_X_LPARAM(lParam);
    windowPoint.y = GET_Y_LPARAM(lParam);
    return OnDoubleClick(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnLeftMouseUp(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    nx::touch::ManipulationResult result1;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    ::ReleaseCapture();
    POINT windowPoint;
    windowPoint.x = GET_X_LPARAM(lParam);
    windowPoint.y = GET_Y_LPARAM(lParam);
    if (IsDragging()) {
        // Mouse dragging end
        m_dragRect.right = windowPoint.x;
        m_dragRect.bottom = windowPoint.y;
        LONG dx = 0;
        LONG dy = 0;
        if (m_lastPoint.x != -1 && m_lastPoint.y != -1) {
            dx = m_dragRect.right - m_lastPoint.x;
            dy = m_dragRect.bottom - m_lastPoint.y;
        }
        result1 = OnDraggingEnd(m_pContext, hWnd, wParam, lParam, m_dragRect, dx, dy, currentTimestampInMilliSeconds);
    } else {
        m_leftBtnUpPoint.x = windowPoint.x;
        m_leftBtnUpPoint.y = windowPoint.y;
        UINT_PTR ret;
        // NOTE: the first SetTimer request is always slow (over 500ms)
        if ((ret = ::SetTimer(hWnd, m_timerIdForDoubleClick, GetDoubleClickTime(), nullptr)) == 0) {
            DWORD lastError = GetLastError();
            LOG(SEVERITY_LEVEL_ERROR) << util::LastError(util::LastErrorArgs(L"SetTimer", lastError));
            ManipulationResult result(false, false);
            return result;
        }
    }
    ManipulationResult result2 = OnLeftMouseUpExt(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds);
    m_draggingStatus = DRAGGING_STATUS_NOT_DRAGGING;
    return ManipulationResult(
               result1.wasHandled || result2.wasHandled,
               result1.requireInvalidateRect || result1.requireInvalidateRect);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    ManipulationResult result;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    if (wParam == m_timerIdForDoubleClick) {
        if (! ::KillTimer(hWnd, m_timerIdForDoubleClick)) {
            LOG(SEVERITY_LEVEL_ERROR) << L"KillTimer failed";
            ManipulationResult result(false, false);
            return result;
        }
        m_draggingStatus = DRAGGING_STATUS_NOT_DRAGGING;
        // Left mouse button single click
        result = OnSingleClick(m_pContext, hWnd, wParam, lParam, m_leftBtnUpPoint, currentTimestampInMilliSeconds);
    } else {
        result.requireInvalidateRect = true;
        result.wasHandled = true;
    }
    return result;
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnTouch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);

    ManipulationResult result;
    result.requireInvalidateRect = true;
    result.wasHandled = true;
    return result;
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnRightMouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    ManipulationResult result;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    POINT windowPoint;
    windowPoint.x = GET_X_LPARAM(lParam);
    windowPoint.y = GET_Y_LPARAM(lParam);
    return OnRightSingleClick(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnMouseWheel(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);

    float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA / 10.0f;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    return OnMouseWheel(m_pContext, hWnd, wParam, lParam, delta, currentTimestampInMilliSeconds);
}

ULONGLONG nx::touch::AbstractManipulationHelper::GetCurrentTimestampInMilliSeconds()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    ULARGE_INTEGER ui;
    ui.HighPart = ft.dwHighDateTime;
    ui.LowPart = ft.dwLowDateTime;
    return ui.QuadPart / 10;
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnGesture( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(message);
    ManipulationResult result;
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    GESTUREINFO gi = {0};
    gi.cbSize = sizeof(gi);
    BOOL bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);
    if (!bResult) {
        LOG(SEVERITY_LEVEL_ERROR) << L"GetGestureInfo failed, err=" << GetLastError();
        result.requireInvalidateRect = false;
        result.wasHandled = false;
        return result;
    }
    POINT windowPoint;
    windowPoint.x = gi.ptsLocation.x;
    windowPoint.y = gi.ptsLocation.y;
    ScreenToClient(hWnd, &windowPoint);

    switch (gi.dwID) {
    case GID_BEGIN:
        result = OnGestureBegin(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi);
        break;
    case GID_END:
        result = OnGestureEnd(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi);
        break;
    case GID_ZOOM:
        switch (gi.dwFlags) {
        case GF_BEGIN:
            m_gestureArgument = LODWORD(gi.ullArguments);
            m_lastPoint = windowPoint;
            result = OnZoom(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi, windowPoint, 0.0f);
            break;
        default:
            POINT zoomCenterPoint;
            zoomCenterPoint.x = (m_lastPoint.x + windowPoint.x) / 2;
            zoomCenterPoint.y = (m_lastPoint.y + windowPoint.y) / 2;
            FLOAT zoomFactor = static_cast<FLOAT>(LODWORD(gi.ullArguments)) / static_cast<FLOAT>(m_gestureArgument);
            result = OnZoom(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi, zoomCenterPoint, zoomFactor);
            m_gestureArgument = LODWORD(gi.ullArguments);
            m_lastPoint = windowPoint;
            break;
        }
        break;
    case GID_PAN:
        switch (gi.dwFlags) {
        case GF_BEGIN:
            m_lastPoint = windowPoint;
            result = OnPan(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi, 0, 0);
            break;
        default:
            result = OnPan(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi,
                           windowPoint.x - m_lastPoint.x,
                           windowPoint.y - m_lastPoint.y);
            m_lastPoint = windowPoint;
            break;
        }
        break;
    case GID_ROTATE:
        switch (gi.dwFlags) {
        case GF_BEGIN:
            m_lastPoint = windowPoint;
            m_gestureArgument = 0;
            result = OnRotate(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi, windowPoint, 0.0f);
            break;
        default:
            FLOAT rotateAngle = static_cast<FLOAT>(GID_ROTATE_ANGLE_FROM_ARGUMENT(LODWORD(gi.ullArguments)) - GID_ROTATE_ANGLE_FROM_ARGUMENT(m_gestureArgument));
            result = OnRotate(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi, windowPoint, rotateAngle);
            m_gestureArgument = LODWORD(gi.ullArguments);
            break;
        }
        break;
    case GID_TWOFINGERTAP:
        result = OnTwoFingerTap(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi);
        break;
    case GID_PRESSANDTAP:
        result = OnPressAndTap(m_pContext, hWnd, wParam, lParam, windowPoint, currentTimestampInMilliSeconds, &gi);
        break;
    }

    CloseGestureInfoHandle((HGESTUREINFO)lParam);
    return result;
}

void nx::touch::AbstractManipulationHelper::SetMouseCursor( MOUSE_CURSOR_TYPE mouseCursorType )
{
    switch (mouseCursorType) {
    case MOUSE_CURSOR_TYPE_SIZENWSE:
        m_hCursor = LoadCursor(nullptr, IDC_SIZENWSE);
        break;
    case MOUSE_CURSOR_TYPE_SIZENESW:
        m_hCursor = LoadCursor(nullptr, IDC_SIZENESW);
        break;
    case MOUSE_CURSOR_TYPE_SIZEWE:
        m_hCursor = LoadCursor(nullptr, IDC_SIZEWE);
        break;
    case MOUSE_CURSOR_TYPE_SIZENS:
        m_hCursor = LoadCursor(nullptr, IDC_SIZENS);
        break;
    case MOUSE_CURSOR_TYPE_SIZEALL:
        m_hCursor = LoadCursor(nullptr, IDC_SIZEALL);
        break;
    case MOUSE_CURSOR_TYPE_NO:
        m_hCursor = LoadCursor(nullptr, IDC_NO);
        break;
    case MOUSE_CURSOR_TYPE_HAND:
        m_hCursor = LoadCursor(nullptr, IDC_HAND);
        break;
    case MOUSE_CURSOR_TYPE_DEFAULT:
    default:
        m_hCursor = LoadCursor(nullptr, IDC_ARROW);
        break;
    }
    if (m_hCursor != nullptr) {
        SetCursor(m_hCursor);
        m_mouseCursorType = mouseCursorType;
    }
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnSetCursor( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);

    SetCursor(m_hCursor);
    ManipulationResult result;
    result.requireInvalidateRect = true;
    result.wasHandled = true;
    return result;
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnSetFocus( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(message);
    return OnSetFocus(m_pContext, hWnd, wParam, lParam, GetCurrentTimestampInMilliSeconds());
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnKillFocus( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(message);
    return OnKillFocus(m_pContext, hWnd, wParam, lParam, GetCurrentTimestampInMilliSeconds());
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnChar( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(message);
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    if (wParam == 8) {
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_BACKSPACE, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    } else {
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_NORMAL, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::_OnKeyDown( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER(message);
    ULONGLONG currentTimestampInMilliSeconds = GetCurrentTimestampInMilliSeconds();
    switch (wParam) {
    case VK_UP:
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_CURSOR_UP, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    case VK_DOWN:
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_CURSOR_DOWN, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    case VK_RIGHT:
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_CURSOR_RIGHT, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    case VK_LEFT:
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_CURSOR_LEFT, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    case VK_DELETE:
        return OnChar(m_pContext, hWnd, wParam, lParam, CHAR_TYPE_DELETE, static_cast<wchar_t>(wParam), currentTimestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::AbstractManipulationHelper::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    ManipulationResult manipulationResult(false, false);
    switch (message) {
    case WM_CHAR:
        manipulationResult = _OnChar(hWnd, message, wParam, lParam);
        break;
    case WM_KEYDOWN:
        manipulationResult = _OnKeyDown(hWnd, message, wParam, lParam);
        break;
    case WM_ACTIVATE:
        if (WA_INACTIVE == LOWORD(wParam)) {
            // do nothing
            break;
        }
        // do SetFocus
    case WM_SETFOCUS:
        manipulationResult = _OnSetFocus(hWnd, message, wParam, lParam);
        break;
    case WM_KILLFOCUS:
        manipulationResult = _OnKillFocus(hWnd, message, wParam, lParam);
        break;
    case WM_SETCURSOR:
        manipulationResult = _OnSetCursor(hWnd, message, wParam, lParam);
        break;

    case WM_GESTURE:
        manipulationResult = _OnGesture(hWnd, message, wParam, lParam);
        break;

    case WM_MOUSEMOVE:
        manipulationResult = _OnMouseMove(hWnd, message, wParam, lParam);
        break;

    case WM_RBUTTONDOWN:
        manipulationResult = _OnRightMouseDown(hWnd, message, wParam, lParam);
        break;

    case WM_LBUTTONDOWN:
        manipulationResult = _OnLeftMouseDown(hWnd, message, wParam, lParam);
        break;

    case WM_LBUTTONUP:
        manipulationResult = _OnLeftMouseUp(hWnd, message, wParam, lParam);
        break;

    case WM_LBUTTONDBLCLK:
        manipulationResult = _OnLeftMouseDoubleClick(hWnd, message, wParam, lParam);
        break;

    case WM_TIMER:
        manipulationResult = _OnTimer(hWnd, message, wParam, lParam);
        break;
    case WM_MOUSEHWHEEL:
        manipulationResult = _OnMouseWheel(hWnd, message, wParam, lParam);
        break;
    }
    return manipulationResult;
}

std::wostream& operator<< (std::wostream& strm, const GESTUREINFO &gi)
{
    wchar_t *s_id = nullptr;
    switch (gi.dwID) {
    case GID_BEGIN:
        s_id = L"GID_BEGIN";
        break;
    case GID_END:
        s_id = L"GID_END";
        break;
    case GID_ZOOM:
        s_id = L"GID_ZOOM";
        break;
    case GID_PAN:
        s_id = L"GID_PAN";
        break;
    case GID_ROTATE:
        s_id = L"GID_ROTATE";
        break;
    case GID_TWOFINGERTAP:
        s_id = L"GID_TWOFINGERTAP";
        break;
    case GID_PRESSANDTAP:
        s_id = L"GID_PRESSANDTAP";
        break;
    default:
        wchar_t buf[1024];
        wsprintf(buf, L"UNKNOWN(%d)", gi.dwID);
    }

    std::wstring s_flags;
    if ((gi.dwFlags & GF_BEGIN) != 0) {
        s_flags += L"GF_BEGIN ";
    }
    if ((gi.dwFlags & GF_INERTIA) != 0) {
        s_flags += L"GF_INERTIA ";
    }
    if ((gi.dwFlags & GF_END) != 0) {
        s_flags += L"GF_END ";
    }

    strm << L"GESTUREINFO(ID=" << s_id
         << L",Flags=" << gi.dwFlags << L"[" << s_flags << L"]"
         << L",Location=(" << gi.ptsLocation.x << L"," << gi.ptsLocation.y << L"))";
    return strm;
}

std::wostream& operator<< (std::wostream& strm, const GESTURECONFIG &gi)
{
    wchar_t *s_id = nullptr;
    switch (gi.dwID) {
    case GID_BEGIN:
        s_id = L"GID_BEGIN";
        break;
    case GID_END:
        s_id = L"GID_END";
        break;
    case GID_ZOOM:
        s_id = L"GID_ZOOM";
        break;
    case GID_PAN:
        s_id = L"GID_PAN";
        break;
    case GID_ROTATE:
        s_id = L"GID_ROTATE";
        break;
    case GID_TWOFINGERTAP:
        s_id = L"GID_TWOFINGERTAP";
        break;
    case GID_PRESSANDTAP:
        s_id = L"GID_PRESSANDTAP";
        break;
    default:
        wchar_t buf[1024];
        wsprintf(buf, L"UNKNOWN(%d)", gi.dwID);
    }
    strm << L"GESTURECONFIG(ID=" << s_id
         << L",Want=" << gi.dwWant
         << L",Block=" << gi.dwBlock;
    return strm;
}
