#include "MeshObject.h"
#include "ImageTexture.h"

class RenderPanel
{
    protected:

    GLuint FBOtex;
    GLuint FBO;
    GLuint RBO;

    public:

    RenderPanel(RenderPanel &) = delete;
    RenderPanel& operator=(const RenderPanel&) = delete;

    RenderPanel();
    ~RenderPanel();

    virtual inline void genBuffer();
    virtual inline void bindBuffer();

};
