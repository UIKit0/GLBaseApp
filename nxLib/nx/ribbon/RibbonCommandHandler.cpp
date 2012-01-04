#include "stdafx.h"
#include <Shobjidl.h>
#include <propvarutil.h>
#include "nx/nxLib.h"
#include "nx/ribbon/RibbonCommandHandler.h"
#include "nx/ribbon/RibbonFramework.h"

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
#endif

// convert HSB(360, 100, 100) -> HSB(255, 255, 255)
UI_HSBCOLOR UI_HSB_256(unsigned int hue, unsigned int saturation, unsigned int brightness)
{
    return UI_HSB(
               static_cast<BYTE>(hue / 360.0 * 256.0),
               static_cast<BYTE>(saturation / 100.0 * 256.0),
               static_cast<BYTE>(brightness / 100.0 * 256.0));
}

nx::ribbon::RibbonCommandHandler::RibbonCommandHandler(void) :
    m_pRibbonFramework(nullptr),
    m_pUiRibbon(nullptr)
{
}

nx::ribbon::RibbonCommandHandler::~RibbonCommandHandler(void)
{
}

HRESULT nx::ribbon::RibbonCommandHandler::Initialize()
{
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif
    if (m_pRibbonFramework->HasColorChanged()) {
        CComPtr<IPropertyStore> pPropertyStore;

        if (SUCCEEDED(m_pRibbonFramework->GetFramework()->QueryInterface(&pPropertyStore))) {
            PROPVARIANT propvarBackground;
            PROPVARIANT propvarHighlight;
            PROPVARIANT propvarText;

            nx::color::SolidColor backgroundColor;
            nx::color::SolidColor highlightColor;
            nx::color::SolidColor textColor;
            m_pRibbonFramework->GetColor(backgroundColor, highlightColor, textColor);

            UI_HSBCOLOR _backgroundColor = backgroundColor.ToUIHsbColor();
            UI_HSBCOLOR _highlightColor = highlightColor.ToUIHsbColor();
            UI_HSBCOLOR _textColor = textColor.ToUIHsbColor();

            InitPropVariantFromUInt32(_backgroundColor, &propvarBackground);
            InitPropVariantFromUInt32(_highlightColor, &propvarHighlight);
            InitPropVariantFromUInt32(_textColor, &propvarText);

            pPropertyStore->SetValue(UI_PKEY_GlobalBackgroundColor, propvarBackground);
            pPropertyStore->SetValue(UI_PKEY_GlobalHighlightColor, propvarHighlight);
            pPropertyStore->SetValue(UI_PKEY_GlobalTextColor, propvarText);

            pPropertyStore->Commit();
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return S_OK;
}

HRESULT nx::ribbon::RibbonCommandHandler::OnViewChanged(
    UINT32 viewID,
    __in UI_VIEWTYPE typeID,
    __in IUnknown* pView,
    UI_VIEWVERB verb,
    INT32 uReasonCode)
{
    UNREFERENCED_PARAMETER(viewID);
    UNREFERENCED_PARAMETER(uReasonCode);
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = E_NOTIMPL;
    if (UI_VIEWTYPE_RIBBON == typeID) {
        switch (verb) {
        case UI_VIEWVERB_CREATE:
            if (nullptr == m_pUiRibbon) {
                hr = pView->QueryInterface(&m_pUiRibbon);
            }
            break;
        case UI_VIEWVERB_SIZE:
            if (nullptr != m_pUiRibbon) {
                UINT ribbonHeight = GetRibbonHeight();
                PostMessage(m_pRibbonFramework->GetParentHWnd(),
                            WM_RIBBON_RESIZED, static_cast<WPARAM>(ribbonHeight), 0);
            }
            break;
        case UI_VIEWVERB_DESTROY:
            m_pUiRibbon = nullptr;
            hr = S_OK;
            break;
        }
    }

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE(SEVERITY_LEVEL_DEBUG);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonCommandHandler::OnCreateUICommand(
    UINT32 commandId,
    __in UI_COMMANDTYPE typeID,
    __deref_out IUICommandHandler** commandHandler)
{
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif
    *commandHandler = nullptr;

    HRESULT hr = m_pRibbonFramework->NotifyOnCreateUICommand(commandId, typeID, commandHandler);
    if (SUCCEEDED(hr) && *commandHandler == nullptr) {
        hr = QueryInterface(IID_PPV_ARGS(commandHandler));
    }

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonCommandHandler::OnDestroyUICommand(
    UINT32 commandId,
    __in UI_COMMANDTYPE typeID,
    __in_opt IUICommandHandler* commandHandler)
{
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = m_pRibbonFramework->NotifyOnDestroyUICommand(commandId, typeID, commandHandler);

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonCommandHandler::Execute(
    UINT32 commandId,
    UI_EXECUTIONVERB verb,
    __in_opt const PROPERTYKEY* key,
    __in_opt const PROPVARIANT* currentValue,
    __in_opt IUISimplePropertySet* commandExecutionProperties)
{
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = m_pRibbonFramework->NotifyExecute(commandId, verb, key, currentValue, commandExecutionProperties);

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}

HRESULT nx::ribbon::RibbonCommandHandler::UpdateProperty(
    UINT32 commandId,
    __in REFPROPERTYKEY key,
    __in_opt const PROPVARIANT* currentValue,
    __out PROPVARIANT* newValue)
{
#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_ENTER(SEVERITY_LEVEL_DEBUG);
#endif

    HRESULT hr = m_pRibbonFramework->NotifyUpdateProperty(commandId, key, currentValue, newValue);

#ifdef DEBUG_NX_RIBBON_RIBBONEVENTHANDLER
    LOG_LEAVE_HRESULT(SEVERITY_LEVEL_DEBUG, hr);
#endif
    return hr;
}
