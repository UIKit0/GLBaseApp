#include "stdafx.h"
#include "nx/touch/ManipulationHelper.h"

nx::touch::ManipulationHelper::ManipulationHelper() :
    m_pListener(nullptr)
{
}

nx::touch::ManipulationHelper::~ManipulationHelper()
{
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnLeftMouseDownExt( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnLeftMouseDownExt(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnLeftMouseUpExt( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnLeftMouseUpExt(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnSingleClick( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnSingleClick(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnDoubleClick( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnDoubleClick(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnDraggingStart( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnDraggingStart(pContext, hWnd, wParam, lParam, windowDragRect, dx, dy, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnDragging( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnDragging(pContext, hWnd, wParam, lParam, windowDragRect, dx, dy, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnDraggingEnd( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnDragging(pContext, hWnd, wParam, lParam, windowDragRect, dx, dy, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnMouseOver( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnMouseOver(pContext, hWnd, wParam, lParam, windowPoint, dx, dy, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnMouseOut( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnMouseOut(pContext, hWnd, wParam, lParam, windowPoint, dx, dy, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnRightSingleClick( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnRightSingleClick(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnGestureBegin( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnGestureBegin(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnGestureEnd( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnGestureEnd(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnZoom( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT zoomCenterPoint, FLOAT zoomFactor )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnZoom(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo, zoomCenterPoint, zoomFactor);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnPan( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, LONG dx, LONG dy )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnPan(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo, dx, dy);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnRotate( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT rotateCenterPoint, FLOAT rotateAngle )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnRotate(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo, rotateCenterPoint, rotateAngle);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnTwoFingerTap( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnTwoFingerTap(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnPressAndTap( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnPressAndTap(pContext, hWnd, wParam, lParam, windowPoint, timestampInMilliSeconds, pGestureInfo);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnSetFocus( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnSetFocus(pContext, hWnd, wParam, lParam, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnKillFocus( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnKillFocus(pContext, hWnd, wParam, lParam, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnChar( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, CHAR_TYPE charType, wchar_t c, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnChar(pContext, hWnd, wParam, lParam, charType, c, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}

nx::touch::ManipulationResult nx::touch::ManipulationHelper::OnMouseWheel( nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, FLOAT delta, ULONGLONG timestampInMilliSeconds )
{
    if (m_pListener != nullptr) {
        return m_pListener->OnMouseWheel(pContext, hWnd, wParam, lParam, delta, timestampInMilliSeconds);
    }
    return ManipulationResult(false, false);
}
