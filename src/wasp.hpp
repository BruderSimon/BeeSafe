#ifndef WASP_HPP
#define WASP_HPP

#include "game_object.hpp"
#include <cmath>
#include "texture.hpp"

class Wasp : public GameObject{
public:
  ~Wasp(){};
  void update(GLfloat diffTime);
  void render();
  bool cleanUp();
  void init();
  void setVertices(GLfloat posX, GLfloat posY, Texture *texture);
  void setDestination(GLfloat destX, GLfloat destY);
  GLboolean hasHit = false;
  GLfloat X, Y;
private:
  GLuint textureID;
  GLuint VertexArrayID;
  GLuint posVBO, texVBO;
  GLfloat destinationX;
  GLfloat destinationY;
  void updateVertices();
};

#endif
