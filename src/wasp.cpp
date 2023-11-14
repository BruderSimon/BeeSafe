
#include "wasp.hpp"
#include <cmath>
#include <cstdio>
void Wasp::init(){
 
  glGenVertexArrays(1, &VertexArrayID);
  //Generate positionVBO
  glGenBuffers(1, &posVBO);
  //Generate textureVBO
  glGenBuffers(1, &texVBO);
}

void Wasp::setDestination(GLfloat destX, GLfloat destY){
  destinationX = destX;
  destinationY = destY;
}

void Wasp::setVertices(GLfloat posX, GLfloat posY, Texture *texture){
  X = posX;
  Y = posY;
  GLfloat vertices [] = {
    X, Y, 0.0f,  
    X, Y - 0.25f, 0.0f,  
    X+0.25f, Y - 0.25f, 0.0f,
    X+0.25f, Y - 0.25f, 0.0f,
    X+0.25f, Y, 0.0f,
    X, Y, 0.0f,
    };
  glBindVertexArray(VertexArrayID);
  glBindBuffer(GL_ARRAY_BUFFER, posVBO);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  texture->bindTexture(&texVBO, &textureID);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


void Wasp::update(GLfloat deltaTime){

  // Calculate the direction vector
  GLfloat directionX = destinationX - X;
  GLfloat directionY = destinationY - Y;

  GLfloat speed = 0.005f;
  
  // Normalize the direction vector
  GLfloat magnitude = sqrt(directionX * directionX + directionY * directionY);
  directionX /= magnitude;
  directionY /= magnitude;

  // Calculate the change in position
  GLfloat deltaX = speed * directionX * deltaTime;
  GLfloat deltaY = speed * directionY * deltaTime;
  // std::printf("\n Delta X %f \n Delta Y %f" , X - destinationX, Y - destinationY);
  if((X - destinationX) < 0.3f && (Y - destinationY) < 0.2f){
    hasHit = true;
  }else{
    X += deltaX;
    Y += deltaY;
    updateVertices();
  }
  
}

void Wasp::updateVertices(){
   GLfloat vertices [] = {
    X, Y, 0.0f,  
    X, Y - 0.25f, 0.0f,  
    X+0.25f, Y - 0.25f, 0.0f,
    X+0.25f, Y - 0.25f, 0.0f,
    X+0.25f, Y, 0.0f,
    X, Y, 0.0f,
    };
  glBindBuffer(GL_ARRAY_BUFFER, posVBO);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VertexArrayID);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
}


void Wasp::render(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glBindVertexArray(VertexArrayID);

    // Attribute pointers for position and texture
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool Wasp::cleanUp(){
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteBuffers(1, &posVBO);
  glDeleteBuffers(1, &texVBO);
  return true;
}
