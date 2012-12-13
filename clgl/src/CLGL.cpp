//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include "CLGL.hpp"

// Constructor
// Set Device Type
CLGL::CLGL(void)
{ 
  try{
    // Device Type
    this->dev = CL_DEVICE_TYPE_DEFAULT;

    // Get the Platforms
    cl::Platform::get(&(this->platform));

    // Get the Devices
    this->platform[0].getDevices(this->dev, &(this->device));
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }

  // Initializate OpenCL Stuff
  this->bufferGL = new std::vector<cl::BufferGL>();
  this->bufferGLMemory = new std::vector<cl::Memory>();
  this->buffer = new std::vector<cl::Buffer>();
  this->kernel = new std::vector<cl::Kernel>();
}

void CLGL::CLGLCreateCommandQueue(void)
{
  try{
    this->commandQueue = cl::CommandQueue(this->context, this->device[0], 0);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }
}

void CLGL::CLGLBuildProgramSource(std::string programName, std::string compilerFlags)
{
  int begin = 0, end = 0, lenth;
  char * buffer = NULL;
  std::fstream programFile;
  std::string programSource;

  // Opens the file  
  programFile.open(programName.data());
  // Get the size of the file
  begin = programFile.tellg();
  programFile.seekg(0, std::ios::end);
  end = programFile.tellg();
  lenth = end - begin;
  buffer = (char*)malloc(sizeof(char) * lenth);
  // Stores the content of the file in buffer
  programFile.read(buffer, lenth);
  programSource = buffer;
  try{
    cl::Program::Sources source(1, std::make_pair(programSource.c_str(), programSource.size()));
    this->program = cl::Program(this->context, source);
    this->program.build(this->device);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    if(!strcmp(error.what(), "clBuildProgram")){
      cl::STRING_CLASS log;
      this->program.getBuildInfo(this->device[0], CL_PROGRAM_BUILD_LOG, &log);
      std::cout << log.data() << std::endl;
    }
    exit(1);
  }
  
  return;
}

void CLGL::CLGLBuildProgramSource(std::string programName)
{
  int lenth;
  char * buffer = NULL;
  std::fstream programFile;
  std::string programSource;

  // Opens the file  
  programFile.open(programName.data());
  // Get the size of the file
  programFile.seekg(0, std::ios::end);
  lenth = programFile.tellg();
  programFile.seekg(0, std::ios::beg);
  buffer = (char*)malloc(sizeof(char) * lenth);
  // Stores the content of the file in buffer
  programFile.read(buffer, lenth);
  programSource = buffer;
  
  try{
    cl::Program::Sources source(1, std::make_pair(programSource.c_str(), lenth));
    this->program = cl::Program(this->context, source);
    this->program.build(this->device);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    if(!strcmp(error.what(), "clBuildProgram")){
      cl::STRING_CLASS log;
      this->program.getBuildInfo(this->device[0], CL_PROGRAM_BUILD_LOG, &log);
      std::cout << log.data() << std::endl;
    }
    exit(1);
  }

  return;
}

std::vector<cl::Kernel>::iterator CLGL::CLGLBuildKernel(std::string kernelFunctionName)
{
  std::vector<cl::Kernel>::iterator pos;

  try{
    pos = this->kernel->end();
    pos = this->kernel->insert(pos, cl::Kernel(this->program, kernelFunctionName.data()));
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }
  return pos;
}

std::vector<cl::Buffer>::iterator CLGL::CLGLLoadDataToDevice(cl_bool blocking, size_t bufferBytesSize, const void * hostMemory, cl_mem_flags flag)
{
  cl::Buffer buff;
  std::vector<cl::Buffer>::iterator pos;

  try{
    buff = cl::Buffer(this->context, flag, bufferBytesSize);
    pos = this->buffer->end();
    pos = this->buffer->insert(pos, buff);
    this->commandQueue.enqueueWriteBuffer(buff, blocking, 0, bufferBytesSize, hostMemory);
    this->commandQueue.finish();
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }

  return pos;  
}

std::vector<cl::BufferGL>::iterator CLGL::CLGLLoadVBODataToDevice(size_t bufferBytesSize, void * hostMemory, cl_mem_flags flag)
{
  std::vector<cl::BufferGL>::iterator pos;
  GLuint id = 0;  // 0 is reserved, glGenBuffersARB() will return non-zero id if success
  GLenum target = GL_ARRAY_BUFFER;
  GLenum usage = GL_DYNAMIC_DRAW; 

  glGenBuffers(1, &id);                          // create a vbo
  glBindBuffer(target, id);                      // activate vbo id to use
  glBufferData(target, bufferBytesSize, hostMemory, usage); // create buffer

  // check data size in VBO is same as input array, if not return 0 and delete VBO
  int bufferSize = 0;
  glGetBufferParameteriv(target, GL_BUFFER_SIZE, &bufferSize);
  if((int)bufferBytesSize != bufferSize){
    glDeleteBuffers(1, &id);
    id = 0;
    std::cout << "[createVBO()] Data size is mismatch with input array\n";
    exit(1);
  }
  //Adds the vbo id
  this->vbo.push_back(id);
  //this was important for working inside blender!
  glBindBuffer(target, 0);
  glFinish();  // Wait for OpenGL to finish

  // Create buffer from OpenGL VBO
  try{
    cl::BufferGL auxBuffer = cl::BufferGL(this->context, flag, id);
    this->bufferGLMemory->push_back(auxBuffer);
    pos = this->bufferGL->end();
    pos = this->bufferGL->insert(pos, auxBuffer);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }
  return pos;
}

void CLGL::CLGLSetArg(int argNum, cl::Memory buffer, cl::Kernel kernel)
{
  kernel.setArg(argNum, buffer);
  return;
}

void CLGL::CLGLRunKernel(std::vector<cl::Memory>* bufferGL, cl::Kernel kernel, int numThreads)
{
  try{
  // Wait for OpenGL finish what it is doing
  glFinish();

  // Get the GL Objects
  this->commandQueue.enqueueAcquireGLObjects(bufferGL, NULL, NULL);

  // Enqueue the kernel
  this->commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(numThreads), cl::NullRange);
  
  // Wait for OpenCL to finish
  this->commandQueue.finish();

  // Release the OpenGL objects
  this->commandQueue.enqueueReleaseGLObjects(bufferGL, NULL, NULL);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    exit(1);
  }
  return;
}

void CLGL::CLGLRunKernel(std::vector<cl::Memory> bufferGL, cl::Kernel kernel, int numThreads)
{
  CLGLRunKernel(&bufferGL, kernel, numThreads);
  
  return;
}

void CLGL::CLGLRunKernel(cl::Kernel kernel, int numThreads)
{
  CLGLRunKernel(this->bufferGLMemory, kernel, numThreads);

  return;
}

void CLGL::CLGLGetDataFromDevice(cl::Buffer *buffer, cl_bool blocking, int bytes_size, void * data)
{
  // Wait until OpenGL finish it's tasks
  glFinish();
  // Wait until OpenCL finish it's tasks
  this->commandQueue.finish();
  // Read the data from the buffer
  this->commandQueue.enqueueReadBuffer(*buffer, blocking, 0, bytes_size, data);
  
  return;
}

std::vector<int>* CLGL::CLGLGetVBO(void)
{
  return &(this->vbo);
}
