#include "stdafx.h"
#include "nx/animation/IAnimationStatusChangedListener.h"
#include "nx/animation/AnimationManagerEventHandler.h"

COM_DECLSPEC_NOTHROW HRESULT nx::animation::AnimationManagerEventHandler::CreateInstance(
    std::weak_ptr<nx::animation::IAnimationStatusChangedListener> animationWindow,
    IUIAnimationManagerEventHandler** ppManagerEventHandler)
{
    AnimationManagerEventHandler* pAnimationManagerEventHandler;
    HRESULT hr = CUIAnimationCallbackBase::CreateInstance(
                     ppManagerEventHandler,
                     &pAnimationManagerEventHandler);
    if (SUCCEEDED(hr)) {
        pAnimationManagerEventHandler->m_animationWindow = animationWindow;
    }
    return hr;
}

nx::animation::AnimationManagerEventHandler::AnimationManagerEventHandler() :
    m_animationWindow()
{
}

nx::animation::AnimationManagerEventHandler::~AnimationManagerEventHandler()
{
}

HRESULT nx::animation::AnimationManagerEventHandler::OnManagerStatusChanged(
    UI_ANIMATION_MANAGER_STATUS newStatus,
    UI_ANIMATION_MANAGER_STATUS previousStatus)
{
    HRESULT hr = S_OK;

    if (newStatus == UI_ANIMATION_MANAGER_BUSY) {
        if (!m_animationWindow.expired()) {
            hr = m_animationWindow.lock()->OnAnimationStatusChanged(newStatus, previousStatus);
        }
    }

    return hr;
}
