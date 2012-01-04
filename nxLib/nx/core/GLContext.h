#ifndef NX_CORE_GLCONTEXT_H_
#define NX_CORE_GLCONTEXT_H_

#include "nx/nxLib.h"
#include "nx/event/IGLRenderEventListener.h"

namespace nx
{
namespace core
{

class GLContext
{
private:
    HWND m_hWnd;
    HGLRC m_hglrc;
    nx::event::IGLRenderEventListener *m_pRenderEventListener;
    bool m_isPrepared;

public:
    GLContext();
    virtual ~GLContext();
    void SetHWnd(HWND hWnd) {
        m_hWnd = hWnd;
    }
    void SetRenderEventListener(nx::event::IGLRenderEventListener *pRenderEventListener) {
        m_pRenderEventListener = pRenderEventListener;
    }
    HGLRC GetHGLRC() const {
        return m_hglrc;
    }
    void Initialize();
    void OnResize(UINT width, UINT height);
    void OnRender();

    GLuint CompileShaderFromResource(PCWSTR pszResource, GLenum shaderType);
};

} // core
} // nx

#endif // NX_CORE_GLCONTEXT_H_