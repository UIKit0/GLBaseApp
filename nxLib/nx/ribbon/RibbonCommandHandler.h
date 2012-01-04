#ifndef NX_RIBBON_RIBBONEVENTHANDLER_H_
#define NX_RIBBON_RIBBONEVENTHANDLER_H_

#include "nx/nxLib.h"

namespace nx
{
namespace ribbon
{

class RibbonCommandHandler :
    public CComObjectRootEx<CComMultiThreadModel>,
    public IUIApplication,
    public IUICommandHandler
{
private:
    RibbonFramework *m_pRibbonFramework;
    IUIRibbon *m_pUiRibbon;

public:
    BEGIN_COM_MAP(RibbonCommandHandler)
    COM_INTERFACE_ENTRY(IUIApplication)
    COM_INTERFACE_ENTRY(IUICommandHandler)
    END_COM_MAP()

    RibbonCommandHandler(void);
    ~RibbonCommandHandler(void);
    void SetRibbonFramework(RibbonFramework *pRibbonFactory) {
        m_pRibbonFramework = pRibbonFactory;
    }
    HRESULT Initialize();
    UINT GetRibbonHeight() const {
        UINT ribbonHeight = 0;
        m_pUiRibbon->GetHeight(&ribbonHeight);
        return ribbonHeight;
    }

    STDMETHOD(OnViewChanged)(
        UINT32 nViewID,
        __in UI_VIEWTYPE typeID,
        __in IUnknown* pView,
        UI_VIEWVERB verb,
        INT32 uReasonCode);

    STDMETHOD(OnCreateUICommand)(
        UINT32 commandId,
        __in UI_COMMANDTYPE typeID,
        __deref_out IUICommandHandler** commandHandler);

    STDMETHOD(OnDestroyUICommand)(
        UINT32 commandId,
        __in UI_COMMANDTYPE typeID,
        __in_opt IUICommandHandler* commandHandler);

    STDMETHODIMP Execute(
        UINT32 commandId,
        UI_EXECUTIONVERB verb,
        __in_opt const PROPERTYKEY* key,
        __in_opt const PROPVARIANT* currentValue,
        __in_opt IUISimplePropertySet* commandExecutionProperties);

    STDMETHODIMP UpdateProperty(
        UINT32 commandId,
        __in REFPROPERTYKEY key,
        __in_opt const PROPVARIANT* currentValue,
        __out PROPVARIANT* newValue);

};

}
}

#endif // NX_RIBBON_RIBBONEVENTHANDLER_H_