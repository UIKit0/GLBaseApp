#ifndef NX_ANIMATION_IANIMATIONWINDOW_H_
#define NX_ANIMATION_IANIMATIONWINDOW_H_

#include "nx/nxLib.h"

namespace nx
{
namespace animation
{
/**
 * アニメーションのステータス変更の通知を行うためのリスナー.
 */
class IAnimationStatusChangedListener
{
public:
    /**
     * アニメーションステータスの変更の通知.
     * @param[in] newStatus 新しいステータス(UI_ANIMATION_MANAGER_IDLE, UI_ANIMATION_MANAGER_BUSY)
     * @param[in] previousStatus 以前のステータス(UI_ANIMATION_MANAGER_IDLE, UI_ANIMATION_MANAGER_BUSY)
     */
    virtual HRESULT OnAnimationStatusChanged(
        UI_ANIMATION_MANAGER_STATUS newStatus,
        UI_ANIMATION_MANAGER_STATUS previousStatus) = 0;
};
}
}

#endif // NX_ANIMATION_IANIMATIONWINDOW_H_