//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include "CLGL.hpp"

// Constructor
// Set Device Type
CLGL::CLGL()
{ 
  // GL related variables //
  this->window_width = 800;
  this->window_height = 600;
  this->glutWindowHandle = 0;
  this->translate_z = -1.f;

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
  }

  // Initializate OpenCL Stuff
  this->bufferGL = new std::vector<cl::Memory>();
  this->buffer = new std::vector<cl::Buffer>();
  this->kernel = new std::vector<cl::Kernel>();
  this->context = NULL;
  this->commandQueue = NULL;
}

void CLGL::CLGLCreateCommandQueue(void)
{
  try{
    this->commandQueue = cl::CommandQueue(this->context, this->device[0], 0);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
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
  
  try{
    this->program = cl::Program(this->context, buffer);
    this->program.build(this->device);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    if(!strcmp(error.what(), "clBuildProgram")){
      cl::STRING_CLASS log;
      this->program.getBuildInfo(this->device[0], CL_PROGRAM_BUILD_LOG, &log);
      std::cout << log.data() << std::endl;
    }
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
  
  try{
    this->program = cl::Program(this->context, buffer);
    this->program.build(this->device);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
    if(!strcmp(error.what(), "clBuildProgram")){
      cl::STRING_CLASS log;
      this->program.getBuildInfo(this->device[0], CL_PROGRAM_BUILD_LOG, &log);
      std::cout << log.data() << std::endl;
    }
  }

  return;
}

cl::Program CLGL::GetProgram(void)
{
  return this->program;
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
  }
  return pos;
}

std::vector<cl::Memory>::iterator CLGL::CLGLVBOMalloc(int bytes_size, cl_mem_flags flag)
{
  std::vector<cl::Memory>::iterator pos;
  GLuint id = 0;  // 0 is reserved, glGenBuffersARB() will return non-zero id if success
  GLenum target = GL_ARRAY_BUFFER;
  GLenum usage = GL_DYNAMIC_DRAW; 

  glGenBuffers(1, &id);                          // create a vbo
  glBindBuffer(target, id);                      // activate vbo id to use
  glBufferData(target, bytes_size, NULL, usage); // create buffer

  // check data size in VBO is same as input array, if not return 0 and delete VBO
  int bufferSize = 0;
  glGetBufferParameteriv(target, GL_BUFFER_SIZE, &bufferSize);
  if(bytes_size != bufferSize){
    glDeleteBuffers(1, &id);
    id = 0;
    std::cout << "[createVBO()] Data size is mismatch with input array\n";
    exit(1);
  }
  //this was important for working inside blender!
  glBindBuffer(target, 0);
  glFinish();  // Wait for OpenGL to finish

  // Create buffer from OpenGL VBO
  try{
    pos = this->bufferGL->end();
    pos = this->bufferGL->insert(pos, cl::BufferGL(this->context, flag, id));
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
  }
  return pos;
}

std::vector<cl::Memory>::iterator CLGL::CLGLVBOMalloc(int bytes_size)
{
  return CLGLVBOMalloc(bytes_size, CL_MEM_READ_WRITE);
}

std::vector<cl::Buffer>::iterator CLGL::CLGLMalloc(int bytes_size, cl_mem_flags flag)
{
  cl::Buffer buffer;
  std::vector<cl::Buffer>::iterator pos;
  
  try{
    buffer = cl::Buffer(this->context, flag, bytes_size);
    pos = this->buffer->end();
    pos = this->buffer->insert(pos, buffer);
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
  }
  return pos;
}

std::vector<cl::Buffer>::iterator CLGL::CLGLMalloc(int bytes_size)
{
  return CLGLMalloc(bytes_size, CL_MEM_READ_WRITE);
}

void CLGL::CLGLLoadDataToDevice(std::vector<cl::Buffer>::iterator it, cl_bool blocking, size_t buffer_bytes_size, const void * hostMemory)
{
  try{
    this->commandQueue.enqueueWriteBuffer(*it, blocking, 0, buffer_bytes_size, hostMemory);
    this->commandQueue.finish();
  }
  catch(cl::Error error){
    std::cout << error.what() << std::endl;
  }

  return;  
}

void CLGL::CLGLSetArg(int argNum, cl::Buffer buffer, cl::Kernel kernel)
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
  CLGLRunKernel(this->bufferGL, kernel, numThreads);

  return;
}

void CLGL::CLGLGetDataFromDevice(cl::Buffer buffer, cl_bool blocking, int bytes_size, void * data)
{
  // Wait until OpenGL finish it's tasks
  glFinish();
  // Wait until OpenCL finish it's tasks
  this->commandQueue.finish();
  // Read the data from the buffer
  this->commandQueue.enqueueReadBuffer(buffer, blocking, 0, bytes_size, data);
  
  return;
}
