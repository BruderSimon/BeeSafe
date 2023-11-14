#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cstdio>
#include <vector>
#include <cmath>
#include "common/stb_image.h"

class GameObject{
 public:
  void update();
  void render();
  bool cleanUp();
  //GLint returnID(){return id;};
private:
  //GLint id;
  
};

#endif
