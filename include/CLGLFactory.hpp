//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#ifndef CL_GLFACTORY_HPP
#define CL_GLFACTORY_HPP

#include "CLGLError.hpp"
#include "CLGL.hpp"

class CLGLFactory { 
  public:
    virtual CLGL* instanciateCLGL(void){return NULL;}
};

#endif
