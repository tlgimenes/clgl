//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include "CLGLWindow.hpp"

int CLGLWindow::mouse_buttons = 0;
float  CLGLWindow::rotate_x = 0.0;
float  CLGLWindow::rotate_y = 0.0;
int CLGLWindow::glutWindowHandle = 0;
float  CLGLWindow::translate_z = -1.f;
int CLGLWindow::window_height = 600;
int CLGLWindow::window_width = 800;
int CLGLWindow::mouse_old_x = 0;
int CLGLWindow::mouse_old_y = 0;

CLGLWindow::CLGLWindow()
{
  glutDisplayFunc(CLGLWindowRender); //main rendering function
  glutTimerFunc(30, CLGLWindowTimerCB, 30); //determin a minimum time between frames
  glutKeyboardFunc(CLGLWindowKeyboard);
  glutMouseFunc(CLGLWindowMouse);
  glutMotionFunc(CLGLWindowMotion);

  glewInit();
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glDisable(GL_DEPTH_TEST);

  // viewport
  glViewport(0, 0, CLGLWindow::window_width, CLGLWindow::window_height);

  // projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, (GLfloat)window_width / (GLfloat) window_height, 0.1, 1000.0);

  // set view matrix
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, translate_z);
}

CLGLWindow::CLGLWindow(int window_height, int window_width)
{
  CLGLWindow::window_height = window_height;
  CLGLWindow::window_width = window_width;

  glutDisplayFunc(CLGLWindowRender); //main rendering function
  glutTimerFunc(30, CLGLWindowTimerCB, 30); //determin a minimum time between frames
  glutKeyboardFunc(CLGLWindowKeyboard);
  glutMouseFunc(CLGLWindowMouse);
  glutMotionFunc(CLGLWindowMotion);

  glewInit();
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glDisable(GL_DEPTH_TEST);

  // viewport
  glViewport(0, 0, CLGLWindow::window_width, CLGLWindow::window_height);

  // projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0, (GLfloat)window_width / (GLfloat) window_height, 0.1, 1000.0);

  // set view matrix
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, translate_z);
}

void CLGLWindowRender(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //this updates the particle system by calling the kernel
  CLGLSim::CLGLRunKernel();

  //render the particles from VBOs
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(5.);

  // Print VBO's
  std::cout << "printing VBO's" << std::endl;
  for(std::vector<int>::iterator vbo = CLGLSim::vbo->begin(); vbo != CLGLSim::vbo->end(); vbo++){
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    std::cout << "print " << *vbo << std::endl;
    glColorPointer(4, GL_FLOAT, 0, 0);
  }
 
  //printf("enable client state\n");
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  //Need to disable these for blender
  glDisableClientState(GL_NORMAL_ARRAY);

  // Draw the simulation points
  glDrawArrays(GL_POINTS, 0, CLGLSim::ParticlesNum);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glutSwapBuffers();
}

void CLGLWindowDestroy(void)
{
  //this makes sure we properly cleanup our OpenCL context
  //delete example;
  if(CLGLWindow::glutWindowHandle)
    glutDestroyWindow(CLGLWindow::glutWindowHandle);
  std::cout << "about to exit!\n" << std::endl;

  exit(0);
}

void CLGLWindowTimerCB(int ms)
{ 
  //this makes sure the appRender function is called every ms miliseconds
  glutTimerFunc(ms, CLGLWindowTimerCB, ms);
  glutPostRedisplay();
}

void CLGLWindowKeyboard(unsigned char key, int x, int y)
{
  //this way we can exit the program cleanly
  switch(key)
  {
    case '\033': // escape quits
    case '\015': // Enter quits    
    case 'Q':    // Q quits
    case 'q':    // q (or escape) quits
      // Cleanup up and quit
      CLGLWindowDestroy();
      break;
  }
}

void CLGLWindowMouse(int button, int state, int x, int y)
{
  //handle mouse interaction for rotating/zooming the view
  if (state == GLUT_DOWN) {
    CLGLWindow::mouse_buttons |= 1<<button;
  } else if (state == GLUT_UP) {
    CLGLWindow::mouse_buttons = 0;
  }

  CLGLWindow::mouse_old_x = x;
  CLGLWindow::mouse_old_y = y;
}

void CLGLWindowMotion(int x, int y)
{
  //hanlde the mouse motion for zooming and rotating the view
  float dx, dy;
  dx = x - CLGLWindow::mouse_old_x;
  dy = y - CLGLWindow::mouse_old_y;

  if (CLGLWindow::mouse_buttons & 1) {
    CLGLWindow::rotate_x += dy * 0.2;
    CLGLWindow::rotate_y += dx * 0.2;
  } else if (CLGLWindow::mouse_buttons & 4) {
    CLGLWindow::translate_z += dy * 0.1;
  }

  CLGLWindow::mouse_old_x = x;
  CLGLWindow::mouse_old_y = y;

  // set view matrix
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, CLGLWindow::translate_z);
  glRotatef(CLGLWindow::rotate_x, 1.0, 0.0, 0.0);
  glRotatef(CLGLWindow::rotate_y, 0.0, 1.0, 0.0);
}

void CLGLWindow::CLGLRunWindow(void)
{
  // Main loop
  glutMainLoop();

  return;
}
