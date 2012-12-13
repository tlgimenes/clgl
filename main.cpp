//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include "CLGLLinux.hpp"
#include "CLGLWindow.hpp"

#include <string>
#include "CL/cl.hpp"

int main(int argc, char *argv[])
{ 
  int numpart = 13;
  std::string windowTitle = "GravSim 1.0";
  CLGLLinux clgl = CLGLLinux(argc, argv, windowTitle);
  
  CLGLWindow window = CLGLWindow();

  std::string programName = "kernel.cl";
  std::string kernelFunctionName = "hello";
 
  try{
    clgl.CLGLCreateContext();
    clgl.CLGLCreateCommandQueue();
    clgl.CLGLBuildProgramSource(programName);

    std::vector<cl::Kernel>::iterator hello;
    hello = clgl.CLGLBuildKernel(kernelFunctionName);

    std::vector<cl::BufferGL>::iterator mem;
    char str[] = "Hello, World!";
  //  char str2[] = "Hello, World!";
    mem = clgl.CLGLLoadVBODataToDevice(numpart, (void*)str, CL_MEM_READ_WRITE);

    CLGLSim::vbo = clgl.CLGLGetVBO();
    CLGLSim::ParticlesNum = numpart;

    clgl.CLGLSetArg(0, *mem, *hello);

    clgl.CLGLRunKernel(*hello, numpart);
  
    window.CLGLRunWindow();

 /*   clgl.CLGLGetDataFromDevice(&(*mem), CL_TRUE, sizeof(char)*13, (void*)str);

    for(int i=0; i < 13; i++)
      str2[i] += 1;
    std::cout << str << std::endl;
    std::cout << str << std::endl;
  */
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
  }

  return 0;
}
