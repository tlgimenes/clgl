//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include <string>
#include "CLGLLinux.hpp"
#include "CLGLFactoryLinux.hpp"

CLGL* CLGLFactoryLinux::instanciateCLGL(int argc, char * argv[], std::string ss){
  return new CLGLLinux(argc, argv, ss);
}
