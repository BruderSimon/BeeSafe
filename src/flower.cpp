#include "flower.hpp"

void Flower::init(){
 
  glGenVertexArrays(1, &VertexArrayID);
  //Generate positionVBO
  glGenBuffers(1, &posVBO);
  //Generate textureVBO
  glGenBuffers(1, &texVBO);
}

void Flower::setVertices(GLfloat posX, GLfloat posY){
  X = posX;
  Y = posY;
  GLfloat vertices [] = {
    X, Y, 0.0f,  
    X, Y - 0.255f, 0.0f,  
    X+0.255f, Y - 0.255f, 0.0f,
    X+0.255f, Y - 0.255f, 0.0f,
    X+0.255f, Y, 0.0f,
    X, Y, 0.0f,
    };
  glBindVertexArray(VertexArrayID);
  glBindBuffer(GL_ARRAY_BUFFER, posVBO);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
    
  setTexture();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Flower::setTexture(){
   GLint width;
   GLint height;
   GLint n;
   unsigned char *data = stbi_load("res/Flower.png", &width, &height, &n, STBI_rgb_alpha);

  GLfloat texCoords[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
};

   
   // Bind texture coordinate VBO
   glBindBuffer(GL_ARRAY_BUFFER, texVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
   
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
   glEnableVertexAttribArray(1);
   
   //Generate the Texture
   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);
   glBindVertexArray(0);
   
   // Configure texture parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
   if(data){
     glTexImage2D(
		  GL_TEXTURE_2D,
		  0,
		  GL_RGBA,
		  width,
		  height,
		  0,
		  GL_RGBA,
		  GL_UNSIGNED_BYTE,
		  data
		  );
     glGenerateMipmap(GL_TEXTURE_2D);
   }else{
     std::printf("Couldn't load Image");
   }
   // Releas Image
   stbi_image_free(data);
  
}

void Flower::render(){
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

bool Flower::cleanUp(){
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteBuffers(1, &posVBO);
  glDeleteBuffers(1, &texVBO);
  return true;
}
