#include "stdafx.h"
#include "nx/ribbon/RibbonFramework.h"
#include "nx/ribbon/RibbonCommandHandler.h"
#include "nx/win/MainWindow.h"
#include "nx/mui/MUI.h"
#include <Shobjidl.h>
#include <propvarutil.h>

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_NX_RIBBON_RIBBONFRAMEWORK
#endif

nx::ribbon::RibbonFramework::RibbonFramework() :
    m_pFramework(nullptr),
    m_pRibbonCommandHandler(nullptr),
    m_mainWnd(),
    m_onCreateFunctors(),
    m_executeFunctors(),
    m_onDestroyFunctors(),
    m_updatePropertyFunctors(),
    m_ribbonEventListeners(),
    m_resourceName(L"APPLICATION_RIBBON"),
    m_backgroundColor(),
    m_highlightColor(),
    m_textColor(),
    m_changeColor(false)
{
}

nx::ribbon::RibbonFramework::~RibbonFramework()
{
}

HRESULT nx::ribbon::RibbonFramework::Initialize( nx::win::MainWindow *mainWnd )
{
#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    m_mainWnd = mainWnd;
    HRESULT hr = CoCreateInstance(CLSID_UIRibbonFramework, nullptr,
                                  CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pFramework));
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"CoCreateInstance failed, hr = " << hr;
        return hr;
    }

    hr = CComObject<nx::ribbon::RibbonCommandHandler>::CreateInstance(&m_pRibbonCommandHandler);
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"CComObject<Ribbon>::CreateInstance failed, hr = " << hr;
        return hr;
    }
    m_pRibbonCommandHandler->SetRibbonFramework(this);

    hr = m_pFramework->Initialize(mainWnd->GetHWnd(), m_pRibbonCommandHandler);
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"IUIFramework::Initialize failed, hr = " << hr;
        return hr;
    }

    hr = m_pFramework->LoadUI(nx::mui::MUI::GetHModule(), L"APPLICATION_RIBBON");
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"IUIFramework::LoadUI failed, hr = " << hr;
        return hr;
    }

    hr = m_pRibbonCommandHandler->Initialize();
    if (FAILED(hr)) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Ribbon::Initialize failed, hr = " << hr;
        return hr;
    }

#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return S_OK;
}

HWND nx::ribbon::RibbonFramework::GetParentHWnd() const
{
    return m_mainWnd->GetHWnd();
}

HRESULT nx::ribbon::RibbonFramework::NotifyOnCreateUICommand( UINT32 commandId, __in UI_COMMANDTYPE typeID, __deref_out IUICommandHandler** commandHandler )
{
#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = S_OK;
    if (m_onCreateFunctors.count(commandId) > 0) {
        hr = m_onCreateFunctors.at(commandId)(typeID, commandHandler);
    } else if (m_ribbonEventListeners.count(commandId) > 0) {
        std::weak_ptr<IRibbonCommandListener> l = m_ribbonEventListeners.at(commandId);
        if (!l.expired()) {
            hr = l.lock()->OnCreateUICommand(typeID, commandHandler);
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonFramework::NotifyExecute( UINT32 commandId, UI_EXECUTIONVERB verb, __in_opt const PROPERTYKEY* key, __in_opt const PROPVARIANT* currentValue, __in_opt IUISimplePropertySet* commandExecutionProperties )
{
#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = S_OK;
    if (m_executeFunctors.count(commandId) > 0) {
        hr = m_executeFunctors.at(commandId)(verb, key, currentValue, commandExecutionProperties);
    } else if (m_ribbonEventListeners.count(commandId) > 0) {
        std::weak_ptr<IRibbonCommandListener> l = m_ribbonEventListeners.at(commandId);
        if (!l.expired()) {
            hr = l.lock()->Execute(verb, key, currentValue, commandExecutionProperties);
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonFramework::NotifyUpdateProperty(
    UINT32 commandId,
    __in REFPROPERTYKEY key,
    __in_opt const PROPVARIANT* currentValue,
    __out PROPVARIANT* newValue )
{
#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = S_OK;
    if (m_updatePropertyFunctors.count(commandId) > 0) {
        hr = m_updatePropertyFunctors.at(commandId)(key, currentValue, newValue);
    } else if (m_ribbonEventListeners.count(commandId) > 0) {
        std::weak_ptr<IRibbonCommandListener> l = m_ribbonEventListeners.at(commandId);
        if (!l.expired()) {
            hr = l.lock()->UpdateProperty(key, currentValue, newValue);
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonFramework::NotifyOnDestroyUICommand(
    UINT32 commandId,
    __in UI_COMMANDTYPE typeID,
    __in_opt IUICommandHandler* commandHandler )
{
#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = E_NOTIMPL;
    if (m_onDestroyFunctors.count(commandId) > 0) {
        hr = m_onDestroyFunctors.at(commandId)(typeID, commandHandler);
    } else if (m_ribbonEventListeners.count(commandId) > 0) {
        std::weak_ptr<IRibbonCommandListener> l = m_ribbonEventListeners.at(commandId);
        if (!l.expired()) {
            hr = l.lock()->OnDestroyUICommand(typeID, commandHandler);
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONFRAMEWORK
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

void nx::ribbon::RibbonFramework::_GetDisplayLocation(HWND hWnd, POINT & pt)
{
    if (pt.x == -1 && pt.y == -1) {
        HRESULT hr = E_FAIL;

        IUIRibbon *pRibbon;
        hr = GetFramework()->GetView(0, IID_PPV_ARGS(&pRibbon));
        if (SUCCEEDED(hr)) {
            UINT32 uRibbonHeight = 0;
            hr = pRibbon->GetHeight(&uRibbonHeight);
            if (SUCCEEDED(hr)) {
                pt.x = 0;
                pt.y = uRibbonHeight;
                ClientToScreen(hWnd, &pt);
            }
            pRibbon->Release();
        }
        if (FAILED(hr)) {
            pt.x = 0;
            pt.y = 0;
        }
    }
}

HRESULT nx::ribbon::RibbonFramework::ShowContextMenu(
    HWND hWnd,
    POINT ptLocation,
    UINT32 contextMenuViewId)
{
    _GetDisplayLocation(hWnd, ptLocation);

    HRESULT hr = E_FAIL;

    IUIContextualUI *pContextualUI = nullptr;

    if (SUCCEEDED(GetFramework()->GetView(contextMenuViewId, IID_PPV_ARGS(&pContextualUI)))) {
        hr = pContextualUI->ShowAtLocation(ptLocation.x, ptLocation.y);
        pContextualUI->Release();
    }

    return hr;
}
