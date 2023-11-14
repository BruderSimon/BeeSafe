#ifndef MENU_HPP
#define MENU_HPP

#include <GL/glew.h>
#include <cstdio>
#include "common/stb_image.h"

class Menu{
public:
  void init();
  void setTexture();
  void render();
  void cleanUp();
private:
  GLuint VertexArrayID, textureID;
  GLuint posVBO;
  GLuint texVBO;
  
};
#endif
