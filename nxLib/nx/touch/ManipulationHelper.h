#ifndef NX_TOUCH_MANIPULATIONHELPER_H_
#define NX_TOUCH_MANIPULATIONHELPER_H_

#include "nx/nxLib.h"
#include "nx/touch/AbstractManipulationHelper.h"
#include "nx/touch/IManipulationEventListener.h"

namespace nx
{
namespace touch
{
class ManipulationHelper :
    public AbstractManipulationHelper
{
private:
    nx::touch::IManipulationEventListener *m_pListener;

public:
    ManipulationHelper();
    virtual ~ManipulationHelper();
    void SetManipulationEventListener(IManipulationEventListener *pManipulationEventListener) {
        m_pListener = pManipulationEventListener;
    }
    virtual ManipulationResult OnLeftMouseDownExt(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnLeftMouseUpExt(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnSingleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnDoubleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnDraggingStart(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnDragging(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnDraggingEnd(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, RECT windowDragRect, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnMouseOver(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnMouseOut(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, LONG dx, LONG dy, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnRightSingleClick(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnGestureBegin(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) override;
    virtual ManipulationResult OnGestureEnd(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) override;
    virtual ManipulationResult OnZoom(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT zoomCenterPoint, FLOAT zoomFactor) override;
    virtual ManipulationResult OnPan(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, LONG dx, LONG dy) override;
    virtual ManipulationResult OnRotate(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo, POINT rotateCenterPoint, FLOAT rotateAngle) override;
    virtual ManipulationResult OnTwoFingerTap(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) override;
    virtual ManipulationResult OnPressAndTap(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, POINT windowPoint, ULONGLONG timestampInMilliSeconds, PGESTUREINFO pGestureInfo) override;
    virtual ManipulationResult OnSetFocus(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnKillFocus(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnChar(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, CHAR_TYPE charType, wchar_t c, ULONGLONG timestampInMilliSeconds) override;
    virtual ManipulationResult OnMouseWheel(nx::core::GLContext *pContext, HWND hWnd, WPARAM wParam, LPARAM lParam, FLOAT delta, ULONGLONG timestampInMilliSeconds) override;
};
}
}

#endif // NX_TOUCH_MANIPULATIONHELPER_H_