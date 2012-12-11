//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

// Allow Exceptions
#ifndef __CL_ENABLE_EXCEPTIONS
#define __CL_ENABLE_EXCEPTIONS
#endif

#ifndef CLGLLinux_HPP
#define CLGLLinux_HPP

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>

#include "GL/glut.h"

#define NUM_PARTICLES 2000

#include "CL/cl.hpp"

#include "CLGL.hpp"

class CLGLLinux: public CLGL
{ 
  public:
    CLGLLinux(int argc, char * argv[]);
    void CLGLCreateContext(void);
};

void appRender();
void init_gl(int argc, char** argv);
void appDestroy(void);
void timerCB(int ms);
void appKeyboard(unsigned char key, int x, int y);
void appMouse(int button, int state, int x, int y);
void appMotion(int x, int y);

#endif
