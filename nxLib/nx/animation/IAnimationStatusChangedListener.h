#ifndef NX_ANIMATION_IANIMATIONWINDOW_H_
#define NX_ANIMATION_IANIMATIONWINDOW_H_

#include "nx/nxLib.h"

namespace nx
{
namespace animation
{
/**
 * �A�j���[�V�����̃X�e�[�^�X�ύX�̒ʒm���s�����߂̃��X�i�[.
 */
class IAnimationStatusChangedListener
{
public:
    /**
     * �A�j���[�V�����X�e�[�^�X�̕ύX�̒ʒm.
     * @param[in] newStatus �V�����X�e�[�^�X(UI_ANIMATION_MANAGER_IDLE, UI_ANIMATION_MANAGER_BUSY)
     * @param[in] previousStatus �ȑO�̃X�e�[�^�X(UI_ANIMATION_MANAGER_IDLE, UI_ANIMATION_MANAGER_BUSY)
     */
    virtual HRESULT OnAnimationStatusChanged(
        UI_ANIMATION_MANAGER_STATUS newStatus,
        UI_ANIMATION_MANAGER_STATUS previousStatus) = 0;
};
}
}

#endif // NX_ANIMATION_IANIMATIONWINDOW_H_