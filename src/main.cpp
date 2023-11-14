
/**
 * Starting Point for the Game
 * Initializing Game and GUI
 * @author Simon Engel
 */

#include "Window.hpp"
#include <cstdio>
#include <thread>
#include <chrono>
using namespace std::chrono; // ns, us, ms, s, h, etc.


int main(){
  Game BeeSafe;
  //Window with glew has to be Initialized before the Game
  Window window(1920, 1080, "BeeSafe", &BeeSafe);
  window.init();
  
  BeeSafe.init();
  
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  
  //Game Loop
  while(BeeSafe.State != Game_End){
    // calculate delta time
    // --------------------
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    if(deltaTime < 15){
      long sleepTime = 15 - deltaTime;
      std::this_thread::sleep_for(nanoseconds(sleepTime * 1000000));
      //std::printf("Sleep for: %long", sleepTime);

      currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
    }
      
      lastFrame = currentFrame;
    
      window.clear();
    
      BeeSafe.update(currentFrame);
    
      BeeSafe.render();

      window.swapBuffer();
    //std::fprintf(stderr, "Game Loop");
  }
  //Clean UP
  window.destroy();
  BeeSafe.end();
}
