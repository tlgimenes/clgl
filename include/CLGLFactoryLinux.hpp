//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#ifndef CLGLFACTORYLINUX_HPP
#define CLGLFACTORYLINUX_HPP

#include "CLGLError.hpp"
#include "CLGLFactory.hpp"

class CLGLFactoryLinux: public CLGLFactory {
  public:
    CLGL* instanciateCLGL(void);  
};

#endif
