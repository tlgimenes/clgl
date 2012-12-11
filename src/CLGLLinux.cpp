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

//  Constructor //
//  Start OpenGL
CLGLLinux::CLGLLinux(int argc, char * argv[]):CLGL(){
  // Init OpenGL
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(this->window_width,this->window_height);
  glutInitWindowPosition (glutGet(GLUT_SCREEN_WIDTH)/2 - this->window_width/2, 
      glutGet(GLUT_SCREEN_HEIGHT)/2 - this->window_height/2);


  std::stringstream ss;
  ss << "Adventures in OpenCL: Part 2, " << NUM_PARTICLES << " particles" << std::ends;
  glutWindowHandle = glutCreateWindow(ss.str().c_str());

  //glutDisplayFunc(appRender); //main rendering function
  glutTimerFunc(30, timerCB, 30); //determin a minimum time between frames
  glutKeyboardFunc(appKeyboard);
  glutMouseFunc(appMouse);
  //glutMotionFunc(appMotion);

  glewInit();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glDisable(GL_DEPTH_TEST);

  // viewport
  glViewport(0, 0, this->window_width, this->window_height);

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

/*//----------------------------------------------------------------------
void appRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //this updates the particle system by calling the kernel
  //example->runKernel();

  //render the particles from VBOs
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(5.);

  //printf("color buffer\n");
  //glBindBuffer(GL_ARRAY_BUFFER, example->c_vbo);
  glColorPointer(4, GL_FLOAT, 0, 0);

  //printf("vertex buffer\n");
  //glBindBuffer(GL_ARRAY_BUFFER, example->p_vbo);
  glVertexPointer(4, GL_FLOAT, 0, 0);

  //printf("enable client state\n");
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  //Need to disable these for blender
  glDisableClientState(GL_NORMAL_ARRAY);

  //printf("draw arrays\n");
  //glDrawArrays(GL_POINTS, 0, example->num);

  //printf("disable stuff\n");
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glutSwapBuffers();
}*/

// mouse controls
int mouse_old_x, mouse_old_y;
int mouse_buttons = 0;
float rotate_x = 0.0, rotate_y = 0.0;
/*
//----------------------------------------------------------------------
void appDestroy(void)
{
  //this makes sure we properly cleanup our OpenCL context
  //delete example;
  if(glutWindowHandle)glutDestroyWindow(glutWindowHandle);
  printf("about to exit!\n");

  exit(0);
}
*/

//----------------------------------------------------------------------
void timerCB(int ms)
{
  //this makes sure the appRender function is called every ms miliseconds
  glutTimerFunc(ms, timerCB, ms);
  glutPostRedisplay();
}


//----------------------------------------------------------------------
void appKeyboard(unsigned char key, int x, int y)
{
  //this way we can exit the program cleanly
  switch(key)
  {
    case '\033': // escape quits
    case '\015': // Enter quits    
    case 'Q':    // Q quits
    case 'q':    // q (or escape) quits
      // Cleanup up and quit
      //appDestroy();
      break;
  }
}


//----------------------------------------------------------------------
void appMouse(int button, int state, int x, int y)
{
  //handle mouse interaction for rotating/zooming the view
  if (state == GLUT_DOWN) {
    mouse_buttons |= 1<<button;
  } else if (state == GLUT_UP) {
    mouse_buttons = 0;
  }

  mouse_old_x = x;
  mouse_old_y = y;
}

/*
//----------------------------------------------------------------------
void appMotion(int x, int y)
{
  //hanlde the mouse motion for zooming and rotating the view
  float dx, dy;
  dx = x - mouse_old_x;
  dy = y - mouse_old_y;

  if (mouse_buttons & 1) {
    rotate_x += dy * 0.2;
    rotate_y += dx * 0.2;
  } else if (mouse_buttons & 4) {
    translate_z += dy * 0.1;
  }

  mouse_old_x = x;
  mouse_old_y = y;

  // set view matrix
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, translate_z);
  glRotatef(rotate_x, 1.0, 0.0, 0.0);
  glRotatef(rotate_y, 0.0, 1.0, 0.0);
}
*/
