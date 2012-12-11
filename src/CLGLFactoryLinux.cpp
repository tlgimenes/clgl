
#include "CLGLLinux.hpp"
#include "CLGLFactoryLinux.hpp"

CLGL* CLGLFactoryLinux::instanciateCLGL(int argc, char * argv[]){
  return new CLGLLinux(argc, argv);
}
