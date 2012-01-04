#ifndef NX_MUI_MUI_H_
#define NX_MUI_MUI_H_

namespace nx
{
namespace mui
{
/**
 * MUI(マルチリンガルユーザインターフェイス).
 */
class MUI
{
private:
    MUI(void);
    ~MUI(void);
    static HMODULE s_hModule;

public:
    /**
     * MUIの初期化.
     * @param[in] dllName 多言語リソースを含むDLL名
     * @return 実行結果
     */
    static HRESULT Initialize(const std::wstring &dllName);
    /**
     * MUIのリソースを含むDLLのモジュールハンドルの取得.
     * @return モジュールハンドル
     */
    static HMODULE GetHModule() {
        return s_hModule;
    }
    /**
     * 文字列リソースの取得.
     * @param[in] uID リソースID
     */
    static const wchar_t * GetString(UINT uID);
};

}
}

#endif // NX_MUI_MUI_H_