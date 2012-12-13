//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/glu.h"

#define GL_GLEXT_PROTOTYPES

#include "GL/glx.h"

#include "CLGLLinux.hpp"
#include "CLGLWindow.hpp"

//  Constructor //
//  Start OpenGL
CLGLLinux::CLGLLinux(int argc, char * argv[],std::string ss):CLGL(){
  // Init OpenGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(CLGLWindow::window_width,CLGLWindow::window_height);
  glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2 - CLGLWindow::window_width/2, 
      glutGet(GLUT_SCREEN_HEIGHT)/2 - CLGLWindow::window_height/2);

  CLGLWindow::glutWindowHandle = glutCreateWindow(ss.c_str());

  glewInit();
}

void CLGLLinux::CLGLCreateContext(void)
{
  // Creates the Properties Array
  cl_context_properties properties[] = 
  {
    CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
    CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(), 
    CL_CONTEXT_PLATFORM, (cl_context_properties) (this->platform[0])(), 
    0
  };
  
  try{
  // Creates the Context
  this->context = cl::Context(this->dev, properties);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
  }
}
