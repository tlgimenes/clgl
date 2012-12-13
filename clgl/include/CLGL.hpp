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

#ifndef CLGL_HPP
#define CLGL_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include <CL/cl.hpp>
#include <fstream>
#include <iostream>

class CLGL 
{
  protected:
  // GL related variables
    std::vector<int> vbo;

  // CL related variables
    std::vector<cl::Platform> platform;
    std::vector<cl::Device> device;
    cl::Context context;
    cl::CommandQueue commandQueue;
    cl::Program program;
    cl_device_type dev;
    std::vector<cl::BufferGL>* bufferGL;
    std::vector<cl::Memory>* bufferGLMemory;
    std::vector<cl::Buffer>* buffer;
    std::vector<cl::Kernel>* kernel;

  public: 
    CLGL(void);
    virtual void CLGLCreateContext(void){};
    void CLGLCreateCommandQueue(void);
    void CLGLBuildProgramSource(std::string programName, std::string compilerFlags);
    void CLGLBuildProgramSource(std::string programName);
    std::vector<cl::BufferGL>::iterator CLGLLoadVBODataToDevice(size_t bufferBytesSize, void * hostMemory, cl_mem_flags flag);
    std::vector<cl::Buffer>::iterator CLGLLoadDataToDevice(cl_bool blocking, size_t bufferBytesSize,const void * hostMemory, cl_mem_flags flag);
    void CLGLSetArg(int argNum, cl::Memory buffer, cl::Kernel kernel);
    void CLGLRunKernel(std::vector<cl::Memory> bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(std::vector<cl::Memory> *bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(cl::Kernel kernel, int numThreads);
    void CLGLGetDataFromDevice(cl::Buffer *buffer,cl_bool blocking, int bytes_size, void *data);
    std::vector<cl::Kernel>::iterator CLGLBuildKernel(std::string kernelFunctionName);
 
    std::vector<int>* CLGLGetVBO(void);
};

#endif
