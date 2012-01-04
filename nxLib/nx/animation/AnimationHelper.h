#ifndef NX_ANIMATION_ANIMATIONHELPER_H_
#define NX_ANIMATION_ANIMATIONHELPER_H_

#include "nx/nxLib.h"
#include "nx/animation/IAnimationStatusChangedListener.h"

namespace nx
{
namespace animation
{
class AnimationHelper :
    public std::enable_shared_from_this<AnimationHelper>
{
private:
    CComPtr<IUIAnimationManager> m_pAnimationManager;
    CComPtr<IUIAnimationTimer> m_pAnimationTimer;
    CComPtr<IUIAnimationTransitionLibrary> m_pTransitionLibrary;
    std::weak_ptr<nx::animation::IAnimationStatusChangedListener> m_animationStatusChangedListener;

public:
    AnimationHelper();
    virtual ~AnimationHelper();
    void Initialize();
    IUIAnimationManager* GetAnimationManager() const {
        return m_pAnimationManager;
    }
    IUIAnimationTimer* GetAnimationTimer() const {
        return m_pAnimationTimer;
    }
    IUIAnimationTransitionLibrary* GetAnimationTransitionLibrary() const {
        return m_pTransitionLibrary;
    }
    void SetAnimationStatusChangedListener(
        std::weak_ptr<nx::animation::IAnimationStatusChangedListener> animationStatusChangedListener) {
        m_animationStatusChangedListener = animationStatusChangedListener;
    }
};
}
}

#endif // NX_ANIMATION_ANIMATIONHELPER_H_