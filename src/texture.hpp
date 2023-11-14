#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "common/stb_image.h"
#include <GL/glew.h>
#include <cstdio>
#include <string>

class Texture{
  
public:
  void loadTexture(const char *path);
  void bindTexture(GLuint *texVBO, GLuint *textureID);
  void release_img();
  
  unsigned char *data;
  GLint width;
  GLint height;
  GLint n;
};

#endif
