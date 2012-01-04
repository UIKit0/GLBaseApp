#ifndef NX_TOUCH_ABSTRACTMANIPULATIONHELPER_H_
#define NX_TOUCH_ABSTRACTMANIPULATIONHELPER_H_

#include "nx/nxLib.h"
#include "nx/touch/ManipulationResult.h"

namespace nx
{
namespace touch
{

enum DRAGGING_STATUS {
    DRAGGING_STATUS_NOT_DRAGGING,
    DRAGGING_STATUS_PREPARE,
    DRAGGING_STATUS_DRAGGING
};

enum MOUSE_CURSOR_TYPE {
    MOUSE_CURSOR_TYPE_DEFAULT,
    MOUSE_CURSOR_TYPE_SIZENWSE,
    MOUSE_CURSOR_TYPE_SIZENESW,
    MOUSE_CURSOR_TYPE_SIZEWE,
    MOUSE_CURSOR_TYPE_SIZENS,
    MOUSE_CURSOR_TYPE_SIZEALL,
    MOUSE_CURSOR_TYPE_NO,
    MOUSE_CURSOR_TYPE_HAND
};

enum CHAR_TYPE {
    CHAR_TYPE_NORMAL,
    CHAR_TYPE_CURSOR_UP,
    CHAR_TYPE_CURSOR_DOWN,
    CHAR_TYPE_CURSOR_LEFT,
    CHAR_TYPE_CURSOR_RIGHT,
    CHAR_TYPE_BACKSPACE,
    CHAR_TYPE_DELETE,
};

/**
 * 抽象マニピュレーションヘルパー.
 */
class AbstractManipulationHelper
{
private:
    nx::core::GLContext *m_pContext;
    /**
     * マスタータイマーID.
     * m_timerIdForDoubleClickなどのタイマーIDが重複しないようにユニークなIDを生成するために使われる。
     */
    static UINT_PTR s_masterTimerId;
    /**
     * 最後にマウスダウン、マウスムーブ、ジェスチャした位置.
     */
    POINT m_lastPoint;
    /**
     * ドラッギングの状態(NOT_DRAGGING, PREPARE, DRAGGING).
     */
    DRAGGING_STATUS m_draggingStatus;
    /**
     * ドラッグの矩形(開始点と終点を囲む矩形).
     */
    RECT m_dragRect;
    /**
     * 左ボタンアップ位置.
     */
    POINT m_leftBtnUpPoint;
    /**
     * ダブルクリック判定用のタイマーのID.
     */
    UINT_PTR m_timerIdForDoubleClick;
    /**
     * 前回のジェスチャーイベントのジェスチャー引数.
     * zoomやrotateを計算するために用いる。
     */
    DWORD m_gestureArgument;
    /**
     * 現在表示しているマウスカーソルのタイプ.
     */
    MOUSE_CURSOR_TYPE m_mouseCursorType;
    /**
     * 現在表示しているマウスカーソルのハンドル.
     */
    HCURSOR m_hCursor;

protected:
    virtual ManipulationResult _OnLeftMouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnMouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnLeftMouseUp(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnLeftMouseDoubleClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnRightMouseDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnTouch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnGesture(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnSetCursor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnSetFocus(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnKillFocus(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnChar(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual ManipulationResult _OnMouseWheel(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    /**
     * コンストラクタ.
     */
    AbstractManipulationHelper(void);
    /**
     * デストラクタ.
     */
    virtual ~AbstractManipulationHelper(void);
    void SetContext(nx::core::GLContext *pContext) {
        m_pContext = pContext;
    }
    nx::core::GLContext* GetContext() const {
        return m_pContext;
    }
    /**
     * マウスカーソルの変更.
     * @param[in] mouseCursorType マウスカーソルタイプ
     */
    void SetMouseCursor(MOUSE_CURSOR_TYPE mouseCursorType);
    /**
     * マウスカーソルの取得.
     * @return 現在のマウスカーソルタイプ.
     */
    MOUSE_CURSOR_TYPE GetMouseCursor() const {
        return m_mouseCursorType;
    }
    /**
     * ミリ秒でのタイムスタンプの取得.
     * @return タイムスタンプ(ミリ秒）
     */
    ULONGLONG GetCurrentTimestampInMilliSeconds();
    /**
     * ドラッギング中かどうかを返す.
     * @return trueならばドラッギング中
     */
    bool IsDragging() const {
        return m_draggingStatus == DRAGGING_STATUS_DRAGGING;
    }
    /**
     * ウィンドウメッセージの処理.
     * 親ウィンドウは自身のWndProc内で本メソッドを呼び出すことで、ManipulationHelperが動作する。
     * この際、戻り値であるManipulationResultのeaternがtrueの場合は、メッセージが処理されたことを
     * 意味する。また、invalidateがtrueの場合は、画面を再描画する必要がある。
     * @return マニピュレーション結果
     */
    ManipulationResult WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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

std::wostream& operator<< (std::wostream& strm, const GESTUREINFO &gi);
std::wostream& operator<< (std::wostream& strm, const GESTURECONFIG &gi);

#endif // NX_TOUCH_ABSTRACTMANIPULATIONHELPER_H_