#ifndef NX_TOUCH_MANIPULATIONRESULT_H_
#define NX_TOUCH_MANIPULATIONRESULT_H_

namespace nx
{
namespace touch
{

/**
 * マニピュレーション結果.
 */
class ManipulationResult
{
public:
    /**
     * コンストラクタ.
     */
    ManipulationResult() :
        wasHandled(false),
        requireInvalidateRect(false) {}
    /**
     * コンストラクタ.
     * @param[in] _wasHandled 処理されたかどうか
     * @param[in] _requireInvalidateRect 再描画が必要かどうか
     */
    ManipulationResult(bool _wasHandled, bool _requireInvalidateRect) :
        wasHandled(_wasHandled),
        requireInvalidateRect(_requireInvalidateRect) {}
    /**
     * 処理されたかどうか.
     */
    bool wasHandled;
    /**
     * 再描画が必要かどうか.
     */
    bool requireInvalidateRect;
};

}
}

#endif // NX_TOUCH_MANIPULATIONRESULT_H_