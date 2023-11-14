/**
 * Game class to define all Game Mechanics
 */

#include "game.hpp"
#include <cstdio>
#include <cstdlib>
#include <random>
#include "texture.hpp"

GLfloat RandomFloat(GLfloat min, GLfloat max);

void Game::init(){
  this->State = Game_Menu;
  score = 0;
  Game::programID = LoadShaders("shader/SimpleVertexshader.vertexshader", "shader/SimpleFragmentshader.fragmentshader");
  texture = new Texture();
  texture->loadTexture("res/Wasp.png");
   
  Flower *flower = new Flower();
  flower = new Flower();
  flower->init();
  flower->setVertices(-0.75f, -0.75f);
  flowerObjects.push_back(flower);

  flower = new Flower();
  flower->init();
  flower->setVertices(-0.35f, -0.75f);
  flowerObjects.push_back(flower);
   
  flower = new Flower();
  flower->init();
  flower->setVertices(0.15f, -0.75f);
  flowerObjects.push_back(flower);
   
  flower = new Flower();
  flower->init();
  flower->setVertices(0.55f, -0.75f);
  flowerObjects.push_back(flower);

  // Bee 1
  Bee *bee = new Bee();
  bee->init();
  bee->setVertices(-0.75f, -0.65f);
  beeObjects.push_back(bee);
   
  // Bee 2
  bee = new Bee();
  bee->init();
  bee->setVertices(-0.35f, -0.65f);
  beeObjects.push_back(bee);
  
  // Bee 3
  bee = new Bee();
  bee->init();
  bee->setVertices(0.15f, -0.65f);
  beeObjects.push_back(bee);

  // Bee 4
  bee = new Bee();
  bee->init();
  bee->setVertices(0.55f, -0.65f);
  beeObjects.push_back(bee);
   
  menu.init();

}

void Game::update(GLfloat currentTime){
  if(this->State == Game_Active){
    //Not A Number
    if(lastTime == NAN)
      lastTime = currentTime;
    
    //Spawn every 2 sec
    if(currentTime - lastTime >= 2.0f){
      // Update Game
      Wasp *wasp = new Wasp();
      srand (time(NULL));
      GLfloat x = RandomFloat(-0.8f, 0.8f);
      //std::printf("Float value: %f", x);
      wasp->init();
      wasp->setVertices(x, 0.75f, texture);

      srand(time(NULL));

      // Generate a random integer between 1 and 4
      int random_integer = rand() % 4 + 1;
      switch(random_integer){
      case 1:
	wasp->setDestination(-0.75f, -0.45f);
	break;
      case 2:
	wasp->setDestination(-0.35f, -0.45f);
	break;
      case 3:
	wasp->setDestination(0.15f, -0.45f);
	break;
      case 4:
	wasp->setDestination(0.55f, -0.45f);
	break;
      }
      waspObjects.push_back(wasp);
      lastTime = currentTime;
    }
    for(int i = 0; i < waspObjects.size(); i++){
      Wasp* object  = waspObjects[i];
      	std::printf("\n BEE %d: Bee.x: %f - %f Bee.y: %f - %f \n Xpos: %f Ypos %f \n"
		    ,i ,object->X, object->X+0.25, object->Y-0.25,object->Y, mouse_x, mouse_y);
      if(processInput){
	std::printf("Process Input for Bee %d \n" , i);
	if((object->X <= mouse_x && mouse_x <= object->X+0.25)
	   && (object->Y-0.25 <= mouse_y && mouse_y <= object->Y)){
	  waspObjects.erase(waspObjects.begin() + i);
	  //object->cleanUp();
	  delete object;
	  // std::printf("Removed \n");
	  score++;
	}
      }
      object->update(currentTime - lastTime);
      if(object->hasHit){
	this->State = Game_Over;
	break;
      }
    }
    processInput = false;
  }else if(this->State == Game_Over){
    score = 0;
   for(int i = 0; i < waspObjects.size(); i++){
     Wasp* object  = waspObjects[i];
     object->cleanUp();
     delete object;
    }
   waspObjects.clear();
   this->State = Game_Menu;
  }
}

void Game::render(){
  glUseProgram(programID);
  if(this->State == Game_Active){ 
    for(Bee *object : beeObjects){
      object->render();
    }
     for(Flower *object : flowerObjects){
      object->render();
    }
    for(Wasp *object : waspObjects){
      object->render();
    }
  }else if(this->State == Game_Menu || this->State == Game_Over){
    menu.render();
  }
}

void Game::end(){
  this->State = Game_Over;
  for(Bee *object : beeObjects){
    object->cleanUp();
  }
 for(Wasp *object : waspObjects){
    object->cleanUp();
  }
 for(Flower *object : flowerObjects){
    object->cleanUp();
  }
 menu.cleanUp();
 texture->release_img();
}


GLfloat RandomFloat(GLfloat min, GLfloat max){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<GLfloat> dis(min, max);

  
  return dis(gen);
}
