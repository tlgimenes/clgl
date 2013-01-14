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

#include "CLGLError.hpp"

class CLGL 
{
  protected:
    // -------------------- //
    // GL related variables //
    // -------------------- // 
    // Vbo id
    std::vector<int> vbo;
    int windowID;

    // -------------------- //
    // CL related variables //
    // -------------------- //
    std::vector<cl::Platform> platform;
    std::vector<cl::Device> device;
    cl::Context context;
    cl::CommandQueue commandQueue;
    cl::Program program;
    cl_device_type dev;
    
    // All OpenGL VBO buffers are stored here
    std::vector<cl::Memory>* bufferGL;
    
    // All OpenCL VBO buffers are stored here
    std::vector<cl::Buffer>* buffer;
    
    // All kernels are stored here
    std::vector<cl::Kernel>* kernel;

    // ----------------- //
    // Protected Methods //
    // ----------------- //
    //Create Context
    virtual void CLGLCreateContext(void){};
    //Create the command queue
    virtual void CLGLCreateCommandQueue(void){};
  
  public: 
    CLGL(void);
    //Start OpenGL OpenCL Interop
    void CLGLStart(int argc, char * argv[], std::string windowName, int windowHeight, int windowWidth);
    
    //Get all the information from device
    void CLGLGetDevicesInfo(cl::Device dev, cl_device_info name, std::string * param);
    void CLGLPrintDevicesInfo(cl_device_info name);
    void CLGLPrintAllInfo(void);

    //Build the source of the kernel
    void CLGLBuildProgramSource(std::string programName, std::string compilerFlags);
    void CLGLBuildProgramSource(std::string programName);
    
    //Build one function in the kernel source code
    cl::Kernel* CLGLBuildKernel(std::string kernelFunctionName);
    
    //Transfer between host and device
    cl::Memory* CLGLLoadVBODataToDevice(size_t bufferBytesSize, void * hostMemory, cl_mem_flags flag);
    cl::Buffer* CLGLLoadDataToDevice(cl_bool blocking, size_t bufferBytesSize,const void * hostMemory, cl_mem_flags flag);
    void CLGLGetDataFromDevice(cl::Buffer *buffer,cl_bool blocking, int bytes_size, void *data);

    //Set the kernel arguments for data on device
    void CLGLSetArg(int argNum, cl::Memory buffer, cl::Kernel kernel);
    //Set the simple kernel arguments
    void CLGLSetArg(int argNum, size_t bytesSize, void* buffer, cl::Kernel kernel);
    
    //Runs the kernel
    void CLGLRunKernel(std::vector<cl::Memory> bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(std::vector<cl::Memory> *bufferGL, cl::Kernel kernel, int numThreads);
    void CLGLRunKernel(cl::Kernel kernel, int numThreads);
    
    //Get Private stuff
    std::vector<cl::Memory>* CLGLGetBufferGL(void);
    std::vector<cl::Buffer>* CLGLGetBuffer(void);
    std::vector<cl::Kernel>* CLGLGetKernel(void);
    std::vector<int>* CLGLGetVBO(void);
    int CLGLGetWindowID(void);
};

#endif
