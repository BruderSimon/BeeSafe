#include "texture.hpp"

void Texture::loadTexture(const char *path){
    data = stbi_load(path, &width, &height, &n, STBI_rgb_alpha);
}

void Texture::bindTexture(GLuint *texVBO, GLuint *textureID){
   
  GLfloat texCoords[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
};

   // Bind texture coordinate VBO
   glBindBuffer(GL_ARRAY_BUFFER, *texVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
   
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
   glEnableVertexAttribArray(1);
   
   //Generate the Texture
   glGenTextures(1, textureID);
   glBindTexture(GL_TEXTURE_2D, *textureID);
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
}

void Texture::release_img(){
     stbi_image_free(data);
  }
