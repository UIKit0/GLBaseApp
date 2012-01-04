#ifndef NX_WIN_MAINWINDOW_H_
#define NX_WIN_MAINWINDOW_H_

#include "nx/nxLib.h"
#include "nx/touch/ManipulationResult.h"

namespace nx
{
namespace win
{
typedef std::function < nx::touch::ManipulationResult(
    std::shared_ptr<nx::win::MainWindow> mainWindow,
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam) > MainWindowMessageFunctor;

/**
 * メインウィンドウ.
 */
class MainWindow :
    public std::enable_shared_from_this<MainWindow>
{
private:
    /**
     * メインウィンドウのウィンドウハンドル.
     */
    HWND m_hwnd;
    /**
     * ウィンドウの希望する幅.
     */
    UINT m_preferredWidth;
    /**
     * ウィンドウの希望する高さ.
     */
    UINT m_preferredHeight;
    /**
     * ウィンドウタイトル.
     */
    std::wstring m_title;
    /**
     * コンテキスト.
     * 実体はNXApplicationにて生成される。
     */
    nx::core::GLContext *m_pContext;
    nx::tsf::TSFManager *m_pTSFManager;
    /**
     * リボンフレームワーク.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::ribbon::RibbonFramework> m_ribbonFramework;
    /**
     * キャンバスウィンドウ.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::win::CanvasWindow> m_canvasWindow;

protected:
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam);

public:
    /**
     * コンストラクタ.
     */
    MainWindow(void);
    /**
     * デストラクタ.
     */
    virtual ~MainWindow(void);
    /**
     * コンテキストの設定.
     * @param[in] context コンテキスト
     */
    void SetContext(nx::core::GLContext *pContext) {
        m_pContext = pContext;
    }
    /**
     * コンテキストの取得.
     * @return コンテキスト
     */
    nx::core::GLContext* GetContext() const {
        return m_pContext;
    }
    void SetTSFManager(nx::tsf::TSFManager *pTSFManager) {
        m_pTSFManager = pTSFManager;
    }
    nx::tsf::TSFManager* GetTSFManager() const {
        return m_pTSFManager;
    }
    /**
     * 希望するウィンドウサイズ.
     * @param[in] preferredWidth 希望するウィンドウ幅
     * @param[in] preferredHeight 希望するウィンドウ高さ
     */
    void SetPreferredSize(UINT preferredWidth, UINT preferredHeight) {
        m_preferredWidth = preferredWidth;
        m_preferredHeight = preferredHeight;
    }
    /**
     * ウィンドウタイトル.
     * @param[in] title ウィンドウタイトル
     */
    void SetTitle(const std::wstring &title) {
        m_title = title;
    }
    /**
     * 初期化.
     * @return 実行結果
     */
    HRESULT Initialize();
    /**
     * WM_CREATEで呼び出されるメソッド.
     * @param[in] hwnd ウィンドウハンドル
     * @param[in] message ウィンドウメッセージ
     * @param[in] wParam WPARAM
     * @param[in] lParam LPARAM
     * @return 実行結果
     */
    HRESULT OnCreate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    /**
     * メッセージループの実行.
     */
    void RunMessageLoop();
    /**
     * リボンフレームワークの取得.
     * @return リボンフレームワーク
     */
    nx::ribbon::RibbonFramework* GetRibbonFramework() const {
        return m_ribbonFramework.get();
    }
    /**
     * リボンの高さの取得.
     * @return リボンの高さ
     */
    UINT GetRibbonHeight() const;
    /**
     * キャンバスウィンドウの取得.
     * @return キャンバスウィンドウ
     */
    nx::win::CanvasWindow* GetCanvasWindow() const {
        return m_canvasWindow.get();
    }
    /**
     * ウィンドウハンドルの取得.
     */
    HWND GetHWnd() const {
        return m_hwnd;
    }
};

}
}

#endif // NX_WIN_MAINWINDOW_H_