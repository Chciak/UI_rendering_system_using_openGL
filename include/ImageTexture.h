#include <GL/gl.h>
#include <string>
#include "Application.h"

class ImageTexture
{
    Application *app;
    GLuint textureID;

    int width, height, channels;

    unsigned char *image;

    ImageTexture();
    ImageTexture(Application &APP, std::string texName);
    ~ImageTexture();
    virtual inline void genTexture();
    virtual inline void bindTexture();
};