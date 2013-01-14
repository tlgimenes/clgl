//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include <string>
#include "CLGLLinux.hpp"
#include "CLGLFactoryLinux.hpp"

CLGL* CLGLFactoryLinux::instanciateCLGL(void){
  return new CLGLLinux();
}
