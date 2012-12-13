//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "CLGL.hpp"
#include "CLGLSim.hpp"

class CLGLWindow
{
  public:
    // mouse controls
    static int window_height, window_width;
    static int mouse_old_x, mouse_old_y;
    static int mouse_buttons;
    static float rotate_x, rotate_y;
    static int glutWindowHandle;
    static float translate_z;

    CLGLWindow(void);
    CLGLWindow(int window_height, int window_width);
    void CLGLRunWindow(void);
};

void CLGLWindowRender(void);
void CLGLWindowDestroy(void);
void CLGLWindowTimerCB(int ms);
void CLGLWindowKeyboard(unsigned char key, int x, int y);
void CLGLWindowMouse(int button, int state, int x, int y);
void CLGLWindowMotion(int x, int y);

#endif
