#include "stdafx.h"
#include "nx/logging/Logging.h"
#include "nx/core/GLContext.h"

nx::core::GLContext::GLContext() :
    m_hWnd(0),
    m_hglrc(0),
    m_pRenderEventListener(nullptr),
    m_isPrepared(false)
{
}

nx::core::GLContext::~GLContext()
{
}

void nx::core::GLContext::Initialize()
{
    assert(m_hWnd != 0);
    assert(m_pRenderEventListener != nullptr);

    HDC hdc = GetDC(m_hWnd);
    if (hdc == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"GetDC failed";
        throw std::runtime_error("GetDC failed");
    }

    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelformat = ChoosePixelFormat(hdc, &pfd);
    if (pixelformat == 0) {
        LOG(SEVERITY_LEVEL_ERROR) << L"ChoosePixelFormat failed";
        throw std::runtime_error("ChoosePixelFormat failed");
    }
    SetPixelFormat(hdc, pixelformat, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    if (hglrc == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"wglCreateContext failed";
        throw std::runtime_error("wglCreateContext failed");
    }
    wglMakeCurrent(hdc, hglrc);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        LOG(SEVERITY_LEVEL_ERROR) << L"glewInit failed";
        throw std::runtime_error("glewInit failed");
    }

    static const int  att[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB,   2,
        WGL_CONTEXT_MINOR_VERSION_ARB,   1,
        WGL_CONTEXT_FLAGS_ARB,           0,
        WGL_CONTEXT_PROFILE_MASK_ARB,    WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    if (wglewIsSupported("WGL_ARB_create_context") == 1) {
        m_hglrc = wglCreateContextAttribsARB(hdc, 0, att);
        if (m_hglrc == nullptr) {
            LOG(SEVERITY_LEVEL_ERROR) << L"wglCreateContextAttribsARB failed";
            throw std::runtime_error("wglCreateContextAttribsARB failed");
        }
        wglMakeCurrent(hdc, m_hglrc);
        wglDeleteContext(hglrc);
    } else {
        m_hglrc = hglrc;
    }

    if (m_hglrc == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Could not get proper HGLRC";
        throw std::runtime_error("Could not get proper HGLRC");
    }

    char *version = (char*)glGetString(GL_VERSION);
    LOG(SEVERITY_LEVEL_INFO) << version;

    if (m_pRenderEventListener != nullptr) {
        m_pRenderEventListener->Prepare(this);
        m_isPrepared = true;
    }
}

void nx::core::GLContext::OnResize( UINT width, UINT height )
{
    if (m_pRenderEventListener != nullptr && m_isPrepared) {
        m_pRenderEventListener->OnResize(this, width, height);
    }
}

void nx::core::GLContext::OnRender()
{
    HDC hdc = GetDC(m_hWnd);
    wglMakeCurrent(hdc, m_hglrc);

    if (m_pRenderEventListener != nullptr && m_isPrepared) {
        m_pRenderEventListener->OnRender(this);
    }

    SwapBuffers(hdc);
    ReleaseDC(m_hWnd, hdc);
}

GLuint nx::core::GLContext::CompileShaderFromResource( PCWSTR pszResource, GLenum shaderType )
{
    HRSRC hResource = ::FindResource(HINST_THISCOMPONENT, pszResource, RT_RCDATA);
    if (hResource == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"Could not find the specified resource";
        throw std::runtime_error("Could not find the specified resource");
    }

    HGLOBAL hResourceData = ::LoadResource(HINST_THISCOMPONENT, hResource);
    if (hResourceData == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"LoadResource failed";
        throw std::runtime_error("LoadResource failed");
    }

    LPVOID pData = ::LockResource(hResourceData);
    if (pData == nullptr) {
        LOG(SEVERITY_LEVEL_ERROR) << L"LockResource failed";
        throw std::runtime_error("LockResource failed");
    }

    GLuint shader = glCreateShader(shaderType);
    const GLchar *source[] = {static_cast<const GLchar*>(pData)};
    const GLint lengths[] = {::SizeofResource(HINST_THISCOMPONENT, hResource)};
    glShaderSource(shader, 1, source, lengths);
    glCompileShader(shader);
    GLint result;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
    if (result == GL_FALSE) {
        LOG(SEVERITY_LEVEL_ERROR) << L"CompileShaderFromResource failed";
        throw std::runtime_error("CompileShaderFromResource failed");
    }
    return shader;
}
