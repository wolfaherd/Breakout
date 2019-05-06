//
//  main.cpp
//  Breakout
//
//  Created by mac on 2019/4/23.
//  Copyright © 2019年 cc. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"
#include "ResourceManager.hpp"
#include <iostream>

//GLFW function declarations
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode);

//The width of the screen
const GLuint SCREEN_WIDTH = 800;
//The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH,SCREEN_HEIGHT);

int main(int argc,char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakoutNew", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();//Call it once to catch glewInit() bug,all other errors are noew from our application.
    
    glfwSetKeyCallback(window, key_callback);
    
    //OpenGL configuration
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    //Initialize game
    Breakout.Init();
    
    //DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    
    //Start Game within Menu State
    Breakout.State = GAME_ACTIVE;
    
    while(!glfwWindowShouldClose(window))
    {
        //Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        
        
        //deltaTime = 0.001f;
        //Manage user input
        Breakout.ProcessInput(deltaTime);
        
        //Updata Game state
        Breakout.Update(deltaTime);
        
        //Render
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
        
        glfwSwapBuffers(window);
    }
    
    //Delte all resources as loaded using the resource manager
    ResourceManager::Clear();
    
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode)
{
    //When a user presses the escape key, we set the WindowShouldClose property to true,closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = GL_TRUE;
        else if(action == GLFW_RELEASE)
            Breakout.Keys[key] = GL_FALSE;
    }
}