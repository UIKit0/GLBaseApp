#ifndef NX_TOUCH_MANIPULATIONRESULT_H_
#define NX_TOUCH_MANIPULATIONRESULT_H_

namespace nx
{
namespace touch
{

/**
 * �}�j�s�����[�V��������.
 */
class ManipulationResult
{
public:
    /**
     * �R���X�g���N�^.
     */
    ManipulationResult() :
        wasHandled(false),
        requireInvalidateRect(false) {}
    /**
     * �R���X�g���N�^.
     * @param[in] _wasHandled �������ꂽ���ǂ���
     * @param[in] _requireInvalidateRect �ĕ`�悪�K�v���ǂ���
     */
    ManipulationResult(bool _wasHandled, bool _requireInvalidateRect) :
        wasHandled(_wasHandled),
        requireInvalidateRect(_requireInvalidateRect) {}
    /**
     * �������ꂽ���ǂ���.
     */
    bool wasHandled;
    /**
     * �ĕ`�悪�K�v���ǂ���.
     */
    bool requireInvalidateRect;
};

}
}

#endif // NX_TOUCH_MANIPULATIONRESULT_H_