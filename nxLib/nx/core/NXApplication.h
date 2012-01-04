#ifndef NX_CORE_NXAPPLICATION_H_
#define NX_CORE_NXAPPLICATION_H_

#include "nx/nxLib.h"

namespace nx
{
namespace core
{
/**
 * アプリケーション.
 */
class NXApplication
{
private:
    /**
     * コンテキスト.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::core::GLContext> m_context;
    /**
     * メインウィンドウ.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::win::MainWindow> m_mainWindow;
    /**
     * TSFマネージャ.
     * ここで実体が生成される。
     */
    std::unique_ptr<nx::tsf::TSFManager> m_tsfManager;
    /**
     * ログファイルパス.
     */
    std::wstring m_logFilePath;
    /**
     * MUI DLL名.
     */
    std::wstring m_muiDllName;
public:
    /**
     * コンストラクタ.
     * @param[in] hInstance 現在のアプリケーションインスタンスのハンドル
     * @param[in] hPrevInstance 前のアプリケーションインスタンスのハンドル(常にNULL)
     * @param[in] lpCmdLine プログラム名を除くコマンドライン
     * @param[in] nCmdShow どのようにアプリケーションを表示するかを制御(最小化して表示など)
     */
    NXApplication(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow);
    /**
     * デストラクタ.
     */
    virtual ~NXApplication() {}
    /**
     * ログファイルパス.
     * ユーザプロファイルの"AppData\Local"フォルダ以下の指定したパスにログが出力される。
     * 必ずフォルダを含むパスを指定しなければならない。つまり、"logfile.log"は不可となり、
     * "folder1\logfile.log"のようにフォルダを指定しなければならない。
     * @param[in] logFilePath ログファイルパス
     */
    void SetLogFilePath(const std::wstring &logFilePath) {
        m_logFilePath = logFilePath;
    }
    /**
     * MUI DLL名.
     * @param[in] muiDllName MUI DLL名
     */
    void SetMUIDllName(const std::wstring &muiDllName) {
        m_muiDllName = muiDllName;
    }
    /**
     * メインウィンドウの取得.
     * @return メインウィンドウ
     */
    nx::win::MainWindow* GetMainWindow() const {
        return m_mainWindow.get();
    }
    /**
     * コンテキストの取得.
     * @return コンテキスト
     */
    nx::core::GLContext* GetContext() const {
        return m_context.get();
    }
    nx::tsf::TSFManager* GetTSFManager() const {
        return m_tsfManager.get();
    }
    /**
     * 初期化.
     * @return 実行結果
     */
    HRESULT Initialize();
    /**
     * メッセージループの実行.
     */
    void RunMessageLoop();
};
}
}

#endif // NX_CORE_NXAPPLICATION_H_