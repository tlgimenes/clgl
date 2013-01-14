//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>

#define GL_GLEXT_PROTOTYPES

#include <GL/glx.h>

#include "CLGLLinux.hpp"
#include "CLGLWindow.hpp"

// ----------- //
// Constructor //
// ----------- //
CLGLLinux::CLGLLinux(void):CLGL(){}

/*
 * Create Context. For each Platform this method must be diferent
 */
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
    std::cout << error.what() << CLGLError::errToStr(error.err())->c_str() << std::endl;
    exit(1);
  }
}

/*
 * Creates the Command Queue. This Method associates the command
 * queue to the first OpenCL device found, if you want another 
 * device just change the index on the device array below
 */
void CLGLLinux::CLGLCreateCommandQueue(void)
{
  try{
    this->commandQueue = cl::CommandQueue(this->context, this->device[0], 0);
  }
  catch(cl::Error error){
    std::cout << error.what() << ' ' << CLGLError::errToStr(error.err()) << std::endl;
    exit(1);
  }
  return;
}
