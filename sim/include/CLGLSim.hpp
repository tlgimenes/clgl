//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#ifndef CLGLSIM_HPP
#define CLGLSIM_HPP

#include <vector>
#include <stdlib.h>

class CLGLSim
{
  public:
    static int ParticlesNum;
    static std::vector<int> *vbo;
    static void CLGLRunKernel(void);
};

#endif
