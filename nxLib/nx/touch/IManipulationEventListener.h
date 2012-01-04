#ifndef NX_TOUCH_IMANIPULATIONEVENTHELPER_H_
#define NX_TOUCH_IMANIPULATIONEVENTHELPER_H_

#include "nx/nxLib.h"

namespace nx
{
namespace touch
{
class IManipulationEventListener
{
public:
    virtual ManipulationResult OnLeftMouseDownExt(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnLeftMouseUpExt(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnSingleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnDoubleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnDraggingStart(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnDragging(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnDraggingEnd(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnMouseOver(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnMouseOut(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnRightSingleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnGestureBegin(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) = 0;
    virtual ManipulationResult OnGestureEnd(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) = 0;
    virtual ManipulationResult OnZoom(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT zoomCenterPoint, FLOAT zoomFactor) = 0;
    virtual ManipulationResult OnPan(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, LONG dx, LONG dy) = 0;
    virtual ManipulationResult OnRotate(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT rotateCenterPoint, FLOAT rotateAngle) = 0;
    virtual ManipulationResult OnTwoFingerTap(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) = 0;
    virtual ManipulationResult OnPressAndTap(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) = 0;
    virtual ManipulationResult OnSetFocus(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnKillFocus(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnChar(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, CHAR_TYPE charType, wchar_t c, ULONGLONG timestampInMilliSeconds) = 0;
    virtual ManipulationResult OnMouseWheel(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, FLOAT delta, ULONGLONG timestampInMilliSeconds) = 0;
};
}
}

#endif // NX_TOUCH_IMANIPULATIONEVENTHELPER_H_