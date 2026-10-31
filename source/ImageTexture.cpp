#include <GL/gl.h>
#include <SOIL2/SOIL2.h>
#include <iostream>

#include "ImageTexture.h"

ImageTexture::ImageTexture(Application &APP, std::string texName)
{
    app = &APP;
    std::string path = std::string(app->shaderDir) + '/' + texName;
    textureID = SOIL_load_OGL_texture(path.data(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(textureID == 0){std::cout << "błąd ładowania tekstury\n";}
}

ImageTexture::~ImageTexture()
{
    SOIL_free_image_data(image);
}

static inline void sextureParam()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

inline void ImageTexture::genTexture()
{
    glGenTextures(1, &textureID);
    bindTexture();
}

inline void ImageTexture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}
