//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#ifndef CL_GLFACTORY_HPP
#define CL_GLFACTORY_HPP

#include "CLGL.hpp"

class CLGLFactory { 
  public:
    virtual CLGL* instanciateCLGL(){return NULL;}
};

#endif
