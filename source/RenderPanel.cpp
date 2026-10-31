#include "RenderPanel.h"
#include "MeshObject.h"
#include <GL/gl.h>
#include <iostream>
#include "Application.h"

static void FBOinit(GLuint &fbo, GLuint &colorTex, GLuint &depthRBO, int xrez, int yrez)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        xrez,
        yrez, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER, 
        GL_COLOR_ATTACHMENT0, 
        GL_TEXTURE_2D, 
        colorTex, 
        0);

    glGenRenderbuffers(1, &depthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
    glRenderbufferStorage(
        GL_RENDERBUFFER, 
        GL_DEPTH24_STENCIL8, 
        xrez, 
        yrez);

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, 
        GL_DEPTH_STENCIL_ATTACHMENT, 
        GL_RENDERBUFFER, 
        depthRBO);
}

RenderPanel::RenderPanel()
{
    FBOinit(FBO, FBOtex, RBO, XREZ, YREZ);
    genBuffer();
    bindBuffer();

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {std::cout << "Framebuffer is not complete\n";}

}


RenderPanel::~RenderPanel()
{
    glDeleteFramebuffers(1, &FBO);
}

inline void RenderPanel::genBuffer()
{
    glGenFramebuffers(1, &FBO);
}

inline void RenderPanel::bindBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}
