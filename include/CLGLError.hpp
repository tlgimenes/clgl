//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

// Allow Exceptions
#ifndef __CL_ENABLE_EXCEPTIONS
#define __CL_ENABLE_EXCEPTIONS
#endif

#ifndef CLGLERROR_HPP
#define CLGLERROR_HPP

#include <string>

#include <CL/cl.hpp>

class CLGLError
{
  public:
    static std::string * errToStr(int err);
};

#endif
