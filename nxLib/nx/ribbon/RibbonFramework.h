#ifndef NX_RIBBON_RIBBONFACTORY_H_
#define NX_RIBBON_RIBBONFACTORY_H_

#include "nx/nxLib.h"
#include "nx/ribbon/IRibbonCommandListener.h"
#include "nx/color/SolidColor.h"

namespace nx
{
namespace ribbon
{

typedef std::function <
HRESULT(
    __in UI_COMMANDTYPE typeID,
    __deref_out IUICommandHandler** commandHandler) >
OnCreateUICommandFunctor;

typedef std::function <
HRESULT(
    UI_EXECUTIONVERB verb,
    __in_opt const PROPERTYKEY* key,
    __in_opt const PROPVARIANT* currentValue,
    __in_opt IUISimplePropertySet* commandExecutionProperties) >
ExecuteFunctor;

typedef std::function <
HRESULT(
    __in REFPROPERTYKEY key,
    __in_opt const PROPVARIANT* currentValue,
    __out PROPVARIANT* newValue) >
UpdatePropertyFunctor;

typedef std::function <
HRESULT(
    __in UI_COMMANDTYPE typeID,
    __in_opt IUICommandHandler* commandHandler) >
OnDestroyUICommandFunctor;

class RibbonFramework
{
private:
    IUIFramework *m_pFramework;
    CComObject<RibbonCommandHandler> *m_pRibbonCommandHandler;
    nx::win::MainWindow *m_mainWnd;
    std::map<UINT32, OnCreateUICommandFunctor> m_onCreateFunctors;
    std::map<UINT32, ExecuteFunctor> m_executeFunctors;
    std::map<UINT32, OnDestroyUICommandFunctor> m_onDestroyFunctors;
    std::map<UINT32, UpdatePropertyFunctor> m_updatePropertyFunctors;
    std::map<UINT32, std::weak_ptr<IRibbonCommandListener>> m_ribbonEventListeners;
    std::wstring m_resourceName;
    nx::color::SolidColor m_backgroundColor;
    nx::color::SolidColor m_highlightColor;
    nx::color::SolidColor m_textColor;
    bool m_changeColor;

protected:
    void _GetDisplayLocation(HWND hWnd, OUT POINT & pt);

public:
    RibbonFramework();
    ~RibbonFramework();
    HRESULT Initialize(nx::win::MainWindow *mainWnd);
    CComObject<RibbonCommandHandler>* GetRibbonCommandHandler() const {
        return m_pRibbonCommandHandler;
    }
    IUIFramework* GetFramework() const {
        return m_pFramework;
    }
    nx::win::MainWindow* GetMainWindow() const {
        return m_mainWnd;
    }
    HWND GetParentHWnd() const;
    void SetResourceName(const std::wstring &resourceName) {
        m_resourceName = resourceName;
    }
    void SetColor(nx::color::SolidColor backgroundColor,
                  nx::color::SolidColor highlightColor,
                  nx::color::SolidColor textColor) {
        m_backgroundColor = backgroundColor;
        m_highlightColor = highlightColor;
        m_textColor = textColor;
        m_changeColor = true;
    }
    bool HasColorChanged() const {
        return m_changeColor;
    }
    void GetColor(nx::color::SolidColor &backgroundColor,
                  nx::color::SolidColor &highlightColor,
                  nx::color::SolidColor &textColor) const {
        backgroundColor = m_backgroundColor;
        highlightColor = m_highlightColor;
        textColor = m_textColor;
    }

    void AddOnCreateUICommandFunctor(UINT32 commandId, OnCreateUICommandFunctor f) {
        m_onCreateFunctors.insert(std::make_pair<UINT32, OnCreateUICommandFunctor>(commandId, f));
    }
    HRESULT NotifyOnCreateUICommand(
        UINT32 commandId,
        __in UI_COMMANDTYPE typeID,
        __deref_out IUICommandHandler** commandHandler);
    void AddExecuteFunctor(UINT32 commandId, ExecuteFunctor f) {
        m_executeFunctors.insert(std::make_pair<UINT32, ExecuteFunctor>(commandId, f));
    }
    HRESULT NotifyExecute(
        UINT32 commandId,
        UI_EXECUTIONVERB verb,
        __in_opt const PROPERTYKEY* key,
        __in_opt const PROPVARIANT* currentValue,
        __in_opt IUISimplePropertySet* commandExecutionProperties);
    void AddUpdatePropertyFunctor(UINT32 commandId, UpdatePropertyFunctor f) {
        m_updatePropertyFunctors.insert(std::make_pair<UINT32, UpdatePropertyFunctor>(commandId, f));
    }
    HRESULT NotifyUpdateProperty(
        UINT32 commandId,
        __in REFPROPERTYKEY key,
        __in_opt const PROPVARIANT* currentValue,
        __out PROPVARIANT* newValue);
    void AddOnDestroyUICommand(UINT32 commandId, OnDestroyUICommandFunctor f) {
        m_onDestroyFunctors.insert(std::make_pair<UINT32, OnDestroyUICommandFunctor>(commandId, f));
    }
    HRESULT NotifyOnDestroyUICommand(
        UINT32 commandId,
        __in UI_COMMANDTYPE typeID,
        __in_opt IUICommandHandler* commandHandler);
    void AddRibbonEventListener(UINT32 commandId, std::weak_ptr<IRibbonCommandListener> l) {
        m_ribbonEventListeners.insert(std::make_pair<UINT32, std::weak_ptr<IRibbonCommandListener>>(commandId, l));
    }
    HRESULT ShowContextMenu(HWND hWnd, POINT ptLocation, UINT32 contextMenuViewId);
};

}
}

#endif // NX_RIBBON_RIBBONFACTORY_H_