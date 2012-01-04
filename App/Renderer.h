#ifndef RENDERER_H_
#define RENDERER_H_

#include "nx/nxLib.h"
#include "nx/event/IGLRenderEventListener.h"

class Renderer :
    public nx::event::IGLRenderEventListener
{
private:
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_programHandle;
    GLuint m_vertexArrayHandle;

public:
    Renderer(void);
    virtual ~Renderer(void);

    virtual void Prepare(nx::core::GLContext *pContext) override;
    virtual void OnResize(nx::core::GLContext *pContext, UINT width, UINT height) override;
    virtual void OnRender(nx::core::GLContext *pContext) override;
};

#endif // RENDERER_H_