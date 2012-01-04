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
 * ���ۃ}�j�s�����[�V�����w���p�[.
 */
class AbstractManipulationHelper
{
private:
    nx::core::GLContext *m_pContext;
    /**
     * �}�X�^�[�^�C�}�[ID.
     * m_timerIdForDoubleClick�Ȃǂ̃^�C�}�[ID���d�����Ȃ��悤�Ƀ��j�[�N��ID�𐶐����邽�߂Ɏg����B
     */
    static UINT_PTR s_masterTimerId;
    /**
     * �Ō�Ƀ}�E�X�_�E���A�}�E�X���[�u�A�W�F�X�`�������ʒu.
     */
    POINT m_lastPoint;
    /**
     * �h���b�M���O�̏��(NOT_DRAGGING, PREPARE, DRAGGING).
     */
    DRAGGING_STATUS m_draggingStatus;
    /**
     * �h���b�O�̋�`(�J�n�_�ƏI�_���͂ދ�`).
     */
    RECT m_dragRect;
    /**
     * ���{�^���A�b�v�ʒu.
     */
    POINT m_leftBtnUpPoint;
    /**
     * �_�u���N���b�N����p�̃^�C�}�[��ID.
     */
    UINT_PTR m_timerIdForDoubleClick;
    /**
     * �O��̃W�F�X�`���[�C�x���g�̃W�F�X�`���[����.
     * zoom��rotate���v�Z���邽�߂ɗp����B
     */
    DWORD m_gestureArgument;
    /**
     * ���ݕ\�����Ă���}�E�X�J�[�\���̃^�C�v.
     */
    MOUSE_CURSOR_TYPE m_mouseCursorType;
    /**
     * ���ݕ\�����Ă���}�E�X�J�[�\���̃n���h��.
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
     * �R���X�g���N�^.
     */
    AbstractManipulationHelper(void);
    /**
     * �f�X�g���N�^.
     */
    virtual ~AbstractManipulationHelper(void);
    void SetContext(nx::core::GLContext *pContext) {
        m_pContext = pContext;
    }
    nx::core::GLContext* GetContext() const {
        return m_pContext;
    }
    /**
     * �}�E�X�J�[�\���̕ύX.
     * @param[in] mouseCursorType �}�E�X�J�[�\���^�C�v
     */
    void SetMouseCursor(MOUSE_CURSOR_TYPE mouseCursorType);
    /**
     * �}�E�X�J�[�\���̎擾.
     * @return ���݂̃}�E�X�J�[�\���^�C�v.
     */
    MOUSE_CURSOR_TYPE GetMouseCursor() const {
        return m_mouseCursorType;
    }
    /**
     * �~���b�ł̃^�C���X�^���v�̎擾.
     * @return �^�C���X�^���v(�~���b�j
     */
    ULONGLONG GetCurrentTimestampInMilliSeconds();
    /**
     * �h���b�M���O�����ǂ�����Ԃ�.
     * @return true�Ȃ�΃h���b�M���O��
     */
    bool IsDragging() const {
        return m_draggingStatus == DRAGGING_STATUS_DRAGGING;
    }
    /**
     * �E�B���h�E���b�Z�[�W�̏���.
     * �e�E�B���h�E�͎��g��WndProc���Ŗ{���\�b�h���Ăяo�����ƂŁAManipulationHelper�����삷��B
     * ���̍ہA�߂�l�ł���ManipulationResult��eatern��true�̏ꍇ�́A���b�Z�[�W���������ꂽ���Ƃ�
     * �Ӗ�����B�܂��Ainvalidate��true�̏ꍇ�́A��ʂ��ĕ`�悷��K�v������B
     * @return �}�j�s�����[�V��������
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