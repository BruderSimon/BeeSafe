#ifndef BEE_HPP
#define BEE_HPP

#include "game_object.hpp"

class Bee : public GameObject{
public:
  ~Bee(){};
  void update();
  void render();
  bool cleanUp();
  void init();
  void setVertices(GLfloat posX, GLfloat posY);
  void setTexture();
private:
  GLuint textureID;
  GLuint VertexArrayID;
  GLuint posVBO, texVBO;
};

#endif
