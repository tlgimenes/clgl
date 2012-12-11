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
  // GL related variables //
    int window_width;
    int window_height;
    float translate_z;
    int glutWindowHandle;

  // CL related variables
    std::vector<cl::Platform> platform;
    std::vector<cl::Device> device;
    cl::Context context;
    cl::CommandQueue commandQueue;
    cl::Program program;
    cl_device_type dev;
    std::vector<cl::Memory>* bufferGL;
    std::vector<cl::Buffer>* buffer;
    std::vector<cl::Kernel>* kernel;

  public: 
    CLGL();
    virtual void CLGLCreateContext(void){};
    void CLGLCreateCommandQueue(void);
    void CLGLBuildProgramSource(std::string programName, std::string compilerFlags);
    void CLGLBuildProgramSource(std::string programName);
    void CLGLLoadDataToDevice(std::vector<cl::Buffer>::iterator it, cl_bool blocking, size_t buffer_bytes_size, const void * hostMemory);
    void CLGLSetArg(int argNum, cl::Buffer buffer, cl::Kernel kernel);
    void CLGLRunKernel(std::vector<cl::Memory> bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(std::vector<cl::Memory> *bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(cl::Kernel kernel, int numThreads);
    void CLGLGetDataFromDevice(cl::Buffer buffer,cl_bool blocking, int bytes_size, void *data);
    std::vector<cl::Kernel>::iterator CLGLBuildKernel(std::string kernelFunctionName);
    std::vector<cl::Memory>::iterator CLGLVBOMalloc(int bytes_size, cl_mem_flags flag);
    std::vector<cl::Memory>::iterator CLGLVBOMalloc(int bytes_size);
    std::vector<cl::Buffer>::iterator CLGLMalloc(int bytes_size, cl_mem_flags flag);
    std::vector<cl::Buffer>::iterator CLGLMalloc(int bytes_size);
};

#endif
