#ifndef NX_WIN_CANVASWINDOW_H_
#define NX_WIN_CANVASWINDOW_H_

#include "nx/nxLib.h"
#include "nx/animation/IAnimationStatusChangedListener.h"

namespace nx
{
namespace win
{

/**
 * キャンバスウィンドウ.
 */
class CanvasWindow :
    public std::enable_shared_from_this<CanvasWindow>
{
private:
    /**
     * アニメーションが更新されたときに描画する.
     * trueの場合、アニメーションが更新されたときのみ更新される。
     * falseの場合、常に更新される(Renderのが呼ばれるとすぐにInvalidate)
     * デフォルトはfalse。
     */
    bool m_renderOnAnimationUpdated;
    /**
     * 水平スクロールバーを表示するかどうか.
     * デフォルトはfalse。
     */
    bool m_enableHorizontalScrollbar;
    /**
     * 垂直スクロールバーを表示するかどうか.
     * デフォルトはfalse。
     */
    bool m_enableVerticalScrollbar;
    /**
     * 初期化されたかどうか.
     */
    bool m_isInitialized;
    /**
     * リボンの高さ.
     */
    UINT m_ribbonHeight;
    /**
     * リボンのコンテキストメニューのView ID.
     */
    UINT32 m_contextMenuViewId;
    /**
     * リボンのコンテキストメニューを表示するかどうか.
     */
    bool m_enableContextMenu;
    /**
     * キャンバスウィンドウのウィンドウハンドル.
     */
    HWND m_hwnd;
    /**
     * コンテキスト.
     * 実体はNXApplicationにて作成される。
     */
    nx::core::GLContext *m_pContext;
    /**
     * メインウィンドウ.
     * 実体はNXApplicationにて作成される。
     */
    nx::win::MainWindow *m_pMainWindow;
    /**
     * マニピュレーションヘルパー.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::touch::ManipulationHelper> m_manipulationHelper;
    /**
     * ジェスチャコンフィギュレーション.
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