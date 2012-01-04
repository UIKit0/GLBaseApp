#ifndef NX_TSF_TSFMANAGER_H_
#define NX_TSF_TSFMANAGER_H_

#include "nx/nxLib.h"

namespace nx
{
namespace tsf
{
/**
 * TSF(Text Service Framework)マネージャ.
 */
class TSFManager
{
private:
    /**
     * アクセラレータハンドル.
     */
    HACCEL m_hAccel;
    /**
     * ウィンドウハンドル.
     */
    HWND m_hWnd;
    /**
     * スレッドマネージャ.
     */
    ITfThreadMgr *m_pThreadMgr;
    /**
     * キーストロークマネージャ.
     */
    ITfKeystrokeMgr *m_pKeyMgr;
    /**
     * メッセージポンプ.
     */
    ITfMessagePump *m_pMsgPump;
    /**
     * カテゴリーマネージャ.
     */
    ITfCategoryMgr *m_pCategoryMgr;
    /**
     * 表示属性マネージャ.
     */
    ITfDisplayAttributeMgr *m_pDisplayAttrMgr;
    /**
     * クライアントID.
     */
    TfClientId m_tfClientID;
    /**
     * TSFがアクティブかどうか.
     */
    bool m_isThreadMgrActivated;

public:
    /**
     * コンストラクタ.
     */
    TSFManager(void);
    /**
     * デストラクタ.
     */
    ~TSFManager(void);
    /**
     * アクセラレータの設定.
     * @param[in] hWnd 指定されたウィンドウのイベントをアクセラレータとして処理する
     * @param[in] hAccel アクセラレータのハンドル
     */
    void SetAccelerator(HWND hWnd, HACCEL hAccel) {
        m_hWnd = hWnd;
        m_hAccel = hAccel;
    }
    /**
     * 初期化.
     */
    void Initialize();
    /**
     * メッセージループの実行.
     * TSFを用いるアプリケーションは、必ず、このメッセージループを呼び出さなければならない。
     */
    int  RunMessageLoop();
    /**
     * スレッドマネージャの取得.
     * ITfThreadMgrは、テキストサービスをアクティブや非アクティブにするためや、
     * ドキュメントマネージャを作成するため、ドキュメントコンテキストフォーカスを
     * メンテナンスするためにアプリケーションとテキストサービスにより使われる。
     * @return スレッドマネージャ
     */
    ITfThreadMgr* GetThreadMgr() const  {
        return m_pThreadMgr;
    }
    /**
     * キーストロークマネージャの取得.
     * ITfKeystrokeMgrは、TSFマネージャにより実装され、キーボードマネージャと
     * やり取りするために、アプリケーションとテキストサービスにより使われる。
     * @return キーストロークマネージャ
     */
    ITfKeystrokeMgr* GetKeystrokeMgr() const {
        return m_pKeyMgr;
    }
    /**
     * メッセージポンプの取得.
     * ITfMessagePumpはTSFマネージャにより実装され、アプリケーションメッセージキューから
     * メッセージを取得するためにアプリケーションにより使われる。本インターフェイスのメソッドは、
     * GetMessageとPeekMessageのラッパーである。本インターフェイスは、必要な事前、事後の
     * メッセージ処理を実行するためことをTSFマネージャに対して可能にする。
     * @return メッセージポンプ
     */
    ITfMessagePump* GetMessagePump() const {
        return m_pMsgPump;
    }
    /**
     * TSFマネージャにより割り当てられたクライアントIDの取得.
     * @return クライアントID
     */
    TfClientId GetClientId() const {
        return m_tfClientID;
    }
    /**
     * カテゴリーマネージャの取得.
     * ITfCategoryMgrは、テキストサービスのためのオブジェクトの
     * カテゴリを管理する。TSFマネージャはこのインターフェイスを実装する。
     * @return カテゴリーマネージャ
     */
    ITfCategoryMgr* GetCatetoryMgr() const {
        return m_pCategoryMgr;
    }
    /**
     * 表示属性マネージャの所得.
     * ITfDisplayAttributeMgrは、TSFマネージャにより実装され、
     * 表示属性を取得、列挙するためにアプリケーションにより使われる。
     * 個々の表示属性は、ITfDisplayAttributeInfoを介してアクセスされる。
     * @return 表示属性マネージャ
     */
    ITfDisplayAttributeMgr* GetDisplayAttributeMgr() const {
        return m_pDisplayAttrMgr;
    }
    /**
     * TSFのアクティベート.
     * @return 実行結果
     */
    HRESULT ActivateTSF();
    /**
     * TSFの非アクティベート.
     * @return 実行結果.
     */
    HRESULT DeactivateTSF();
};

}
}

#endif // NX_TSF_TSFMANAGER_H_