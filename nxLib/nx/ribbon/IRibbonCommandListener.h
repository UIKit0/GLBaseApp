#ifndef NX_RIBBON_IRIBBONEVENTLISTENER_H_
#define NX_RIBBON_IRIBBONEVENTLISTENER_H_

namespace nx
{
namespace ribbon
{
/**
 * リボンイベントリスナー.
 */
class IRibbonCommandListener
{
public:
    /**
     * リボンマークアップにおいて該当コマンドが見つかった場合に呼び出されるメソッド.
     * コマンドハンドラへのポインタを設定すれば、他のコマンドハンドラへイベントを送ることができる。
     * @param[in] typeID コマンドタイプ
     * @param[out] ppCommandHandler コマンドハンドラへのポインタ
     * @return 実行結果
     */
    virtual HRESULT OnCreateUICommand(
        __in UI_COMMANDTYPE typeID,
        __deref_out IUICommandHandler** commandHandler) = 0;
    /**
     * コマンドのExecuteコマンドの処理.
     * @param[in] verb ユーザが開始したアクション
     * @param[in] key 値が変わったプロパティキーへのポインタ(NULLになる可能性もある)
     * @param[in] currentValue プロパティキーの現在値へのポインタ(NULLになる可能性もある)
     * @param[in] commandExecutionProperties コマンドステートプロパティやプロパティ値を含むIUISimplePropertySetへのポインタ
     * @return 実行結果
     */
    virtual HRESULT Execute(
        UI_EXECUTIONVERB verb,
        __in_opt const PROPERTYKEY* key,
        __in_opt const PROPVARIANT* currentValue,
        __in_opt IUISimplePropertySet* commandExecutionProperties) = 0;
    /**
     * プロパティの更新.
     * @param[in] key 更新されたプロパティキー
     * @param[in] currentValue プロパティキーの現在値へのポインタ(NULLになる可能性もある)
     * @param[in] newValue 本メソッドがリターンする際に、プロパティキーの新しい値を指しているポインタ
     * @return 実行結果
     */
    virtual HRESULT UpdateProperty(
        __in REFPROPERTYKEY key,
        __in_opt const PROPVARIANT* currentValue,
        __out PROPVARIANT* newValue) = 0;
    /**
     * アプリケーションウィンドウが破棄される際に呼び出されるメソッド.
     * @param[in] typeID コマンドタイプ
     * @param[in] commandHandler IUICommandHandlerへのポインタ(NULLになる可能性もある)
     */
    virtual HRESULT OnDestroyUICommand(
        __in UI_COMMANDTYPE typeID,
        __in_opt IUICommandHandler* commandHandler) = 0;

};
}
}

#endif // NX_RIBBON_IRIBBONEVENTLISTENER_H_