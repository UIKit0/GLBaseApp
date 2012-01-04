#ifndef NX_EVENT_IGLRENDEREVENTLISTENER_H_
#define NX_EVENT_IGLRENDEREVENTLISTENER_H_

#include "nx/nxLib.h"

namespace nx
{
namespace event
{
class IGLRenderEventListener
{
public:
    virtual void Prepare(nx::core::GLContext *pContext) = 0;
    virtual void OnResize(nx::core::GLContext *pContext, UINT width, UINT height) = 0;
    virtual void OnRender(nx::core::GLContext *pContext) = 0;
};
}
}

#endif // NX_EVENT_IGLRENDEREVENTLISTENER_H_