#ifndef CLGLFACTORYLINUX_HPP
#define CLGLFACTORYLINUX_HPP


#include "CLGLFactory.hpp"

class CLGLFactoryLinux: public CLGLFactory {
  public:
    CLGL* instanciateCLGL(int argc, char * argv[]);  
};

#endif
