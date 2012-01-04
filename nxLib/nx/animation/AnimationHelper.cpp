#include "stdafx.h"
#include "nx/animation/AnimationManagerEventHandler.h"
#include "nx/animation/AnimationHelper.h"

nx::animation::AnimationHelper::AnimationHelper() :
    m_pAnimationManager(nullptr),
    m_pAnimationTimer(nullptr),
    m_pTransitionLibrary(nullptr),
    m_animationStatusChangedListener()
{
}

nx::animation::AnimationHelper::~AnimationHelper()
{
}

void nx::animation::AnimationHelper::Initialize()
{
    HRESULT hr = CoCreateInstance(
                     CLSID_UIAnimationManager,
                     nullptr,
                     CLSCTX_INPROC_SERVER,
                     IID_PPV_ARGS(&m_pAnimationManager));
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(
                 CLSID_UIAnimationTimer,
                 nullptr,
                 CLSCTX_INPROC_SERVER,
                 IID_PPV_ARGS(&m_pAnimationTimer));
    }
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(
                 CLSID_UIAnimationTransitionLibrary,
                 nullptr,
                 CLSCTX_INPROC_SERVER,
                 IID_PPV_ARGS(&m_pTransitionLibrary));
    }
    IUIAnimationTimerUpdateHandler *pTimerUpdateHandler = nullptr;
    if (SUCCEEDED(hr)) {
        hr = m_pAnimationManager->QueryInterface(IID_PPV_ARGS(&pTimerUpdateHandler));
    }
    if (SUCCEEDED(hr)) {
        hr = m_pAnimationTimer->SetTimerUpdateHandler(
                 pTimerUpdateHandler, UI_ANIMATION_IDLE_BEHAVIOR_CONTINUE);  // UI_ANIMATION_IDLE_BEHAVIOR_DISABLE
        pTimerUpdateHandler->Release();
    }
    IUIAnimationManagerEventHandler* pAnimationManagerEventHandler = nullptr;
    if (SUCCEEDED(hr)) {
        hr = nx::animation::AnimationManagerEventHandler::CreateInstance(
                 m_animationStatusChangedListener,
                 &pAnimationManagerEventHandler);
    }
    if (SUCCEEDED(hr)) {
        hr = m_pAnimationManager->SetManagerEventHandler(pAnimationManagerEventHandler);
        pAnimationManagerEventHandler->Release();
    }

    m_pAnimationTimer->Enable();
}
