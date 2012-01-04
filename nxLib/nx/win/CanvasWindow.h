#ifndef NX_WIN_CANVASWINDOW_H_
#define NX_WIN_CANVASWINDOW_H_

#include "nx/nxLib.h"
#include "nx/animation/IAnimationStatusChangedListener.h"

namespace nx
{
namespace win
{

/**
 * �L�����o�X�E�B���h�E.
 */
class CanvasWindow :
    public std::enable_shared_from_this<CanvasWindow>
{
private:
    /**
     * �A�j���[�V�������X�V���ꂽ�Ƃ��ɕ`�悷��.
     * true�̏ꍇ�A�A�j���[�V�������X�V���ꂽ�Ƃ��̂ݍX�V�����B
     * false�̏ꍇ�A��ɍX�V�����(Render�̂��Ă΂��Ƃ�����Invalidate)
     * �f�t�H���g��false�B
     */
    bool m_renderOnAnimationUpdated;
    /**
     * �����X�N���[���o�[��\�����邩�ǂ���.
     * �f�t�H���g��false�B
     */
    bool m_enableHorizontalScrollbar;
    /**
     * �����X�N���[���o�[��\�����邩�ǂ���.
     * �f�t�H���g��false�B
     */
    bool m_enableVerticalScrollbar;
    /**
     * ���������ꂽ���ǂ���.
     */
    bool m_isInitialized;
    /**
     * ���{���̍���.
     */
    UINT m_ribbonHeight;
    /**
     * ���{���̃R���e�L�X�g���j���[��View ID.
     */
    UINT32 m_contextMenuViewId;
    /**
     * ���{���̃R���e�L�X�g���j���[��\�����邩�ǂ���.
     */
    bool m_enableContextMenu;
    /**
     * �L�����o�X�E�B���h�E�̃E�B���h�E�n���h��.
     */
    HWND m_hwnd;
    /**
     * �R���e�L�X�g.
     * ���̂�NXApplication�ɂč쐬�����B
     */
    nx::core::GLContext *m_pContext;
    /**
     * ���C���E�B���h�E.
     * ���̂�NXApplication�ɂč쐬�����B
     */
    nx::win::MainWindow *m_pMainWindow;
    /**
     * �}�j�s�����[�V�����w���p�[.
     * �����Ŏ��̂����������B
     */
    std::unique_ptr<nx::touch::ManipulationHelper> m_manipulationHelper;
    /**
     * �W�F�X�`���R���t�B�M�����[�V����.
     */
    std::vector<GESTURECONFIG> m_gestureConfig;

    std::unique_ptr<nx::animation::AnimationHelper> m_animationHelper;

protected:
    void _SetGestureConfigs(HWND hWnd);

public:
    CanvasWindow(void);
    virtual ~CanvasWindow(void);
    void SetContext(nx::core::GLContext *pContext) {
        m_pContext = pContext;
    }
    nx::core::GLContext* GetContext() const {
        return m_pContext;
    }
    void SetMainWindow(nx::win::MainWindow *pMainWindow) {
        m_pMainWindow = pMainWindow;
    }
    nx::win::MainWindow* GetMainWindow() const {
        return m_pMainWindow;
    }
    void SetRenderOnAnimationUpdated(bool renderOnAnimationUpdated) {
        m_renderOnAnimationUpdated = renderOnAnimationUpdated;
    }
    void SetEnableHorizontalScrollbar(bool enableHorizontalScrollbar) {
        m_enableHorizontalScrollbar = enableHorizontalScrollbar;
    }
    void SetEnableVerticalScrollbar(bool enableVerticalScrollbar) {
        m_enableVerticalScrollbar = enableVerticalScrollbar;
    }
    HWND GetHWnd() const {
        return m_hwnd;
    }
    void SetContextMenuViewId(UINT32 contextMenuViewId) {
        m_contextMenuViewId = contextMenuViewId;
    }
    void SetEnableContextMenu(bool enableContextMenu) {
        m_enableContextMenu = enableContextMenu;
    }
    void SetGestureConfig(const std::vector<GESTURECONFIG> &gestureConfig) {
        m_gestureConfig = gestureConfig;
    }
    bool IsInitialized(void) {
        return m_isInitialized;
    }
    void Initialize();
    void InitializeAfterCreate();
    void OnCreate();
    void OnRender();
    void OnResize(UINT width, UINT height);
    void OnContextMenu(LPARAM lParam);
    void ResizeByParentResized();
    void ResizeByRibbonResized(UINT ribbonHeight);
    void Invalidate();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}
}

#endif // NX_WIN_CANVASWINDOW_H_