#include "game_object.hpp"

class Flower{
public:
  ~Flower(){cleanUp();};
  void render();
  bool cleanUp();
  void init();
  void setVertices(GLfloat posX, GLfloat posY);
  void setTexture();
private:
  GLfloat X, Y;
  GLuint textureID;
  GLuint VertexArrayID;
  GLuint posVBO, texVBO;
};
