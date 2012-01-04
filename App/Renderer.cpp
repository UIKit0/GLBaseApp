#include "StdAfx.h"
#include "nx/core/GLContext.h"
#include "Renderer.h"

Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}

void Renderer::Prepare(nx::core::GLContext *pContext)
{
    m_vertexShader = pContext->CompileShaderFromResource(MAKEINTRESOURCE(IDR_SHADER_VS), GL_VERTEX_SHADER);
    m_fragmentShader = pContext->CompileShaderFromResource(MAKEINTRESOURCE(IDR_SHADER_FS), GL_FRAGMENT_SHADER);
    m_programHandle = glCreateProgram();
    glBindAttribLocation(m_programHandle, 0, "VertexPosition");
    glBindAttribLocation(m_programHandle, 1, "VertexColor");
    glAttachShader(m_programHandle, m_vertexShader);
    glAttachShader(m_programHandle, m_fragmentShader);
    glLinkProgram(m_programHandle);
    GLint status;
    glGetProgramiv( m_programHandle, GL_LINK_STATUS, &status );
    assert(status != GL_FALSE);
    glUseProgram(m_programHandle);
    //glBindFragDataLocation(m_program, 0, "FragColor");

    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        -0.0f, 0.8f, 0.0f
    };

    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    // Create the buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    // Populate the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData,
                 GL_STATIC_DRAW);
    // Populate the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData,
                 GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays( 1, &m_vertexArrayHandle );
    glBindVertexArray(m_vertexArrayHandle);
    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0); // Vertex position
    glEnableVertexAttribArray(1); // Vertex color
    // Map index 0 to the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0,
                           (GLubyte *)NULL );
    // Map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0,
                           (GLubyte *)NULL );
}

void Renderer::OnResize(nx::core::GLContext *pContext, UINT width, UINT height)
{
	UNREFERENCED_PARAMETER(pContext);
    glViewport(0, 0, width, height);
}

void Renderer::OnRender(nx::core::GLContext *pContext)
{
	UNREFERENCED_PARAMETER(pContext);
    glClearColor( 0.0f, 0.0f, 0.3f, 0.0f );
    glClearDepth( 1.0f );
    glClearStencil( 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glBindVertexArray(m_vertexArrayHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
}
