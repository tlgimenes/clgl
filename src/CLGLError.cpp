//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

#include <string>

#include "CLGLError.hpp"

/*#define CASE(cl_error, STR) case cl_error: \
                    str = (char*)malloc(sizeof(char) * (strlen(STR)));  \
                    strcpy((char*)STR, str);  \
                    return str;
*/
#define CASE(cl_error, STR) case cl_error: \
                              return new std::string(STR);

std::string * CLGLError::errToStr(int err)
{
  switch(err){
    CASE(CL_SUCCESS, "CL_SUCCESS")
    CASE(CL_DEVICE_NOT_FOUND, "CL_DEVICE_NOT_FOUND") 
    CASE(CL_DEVICE_NOT_AVAILABLE, "CL_DEVICE_NOT_AVAILABLE") 
    CASE(CL_COMPILER_NOT_AVAILABLE, "CL_COMPILER_NOT_AVAILABLE") 
    CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE, "CL_MEM_OBJECT_ALLOCATION_FAILURE") 
    CASE(CL_OUT_OF_RESOURCES, "CL_OUT_OF_RESOURCES") 
    CASE(CL_OUT_OF_HOST_MEMORY, "CL_OUT_OF_HOST_MEMORY") 
    CASE(CL_PROFILING_INFO_NOT_AVAILABLE, "CL_PROFILING_INFO_NOT_AVAILABLE") 
    CASE(CL_MEM_COPY_OVERLAP, "CL_MEM_COPY_OVERLAP") 
    CASE(CL_IMAGE_FORMAT_MISMATCH, "CL_IMAGE_FORMAT_MISMATCH") 
    CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED, "CL_IMAGE_FORMAT_NOT_SUPPORTED") 
    CASE(CL_BUILD_PROGRAM_FAILURE, "CL_BUILD_PROGRAM_FAILURE") 
    CASE(CL_MAP_FAILURE, "CL_MAP_FAILURE") 
    CASE(CL_INVALID_VALUE, "CL_INVALID_VALUE") 
    CASE(CL_INVALID_DEVICE_TYPE, "CL_INVALID_DEVICE_TYPE") 
    CASE(CL_INVALID_PLATFORM, "CL_INVALID_PLATFORM") 
    CASE(CL_INVALID_DEVICE, "CL_INVALID_DEVICE") 
    CASE(CL_INVALID_CONTEXT, "CL_INVALID_CONTEXT") 
    CASE(CL_INVALID_QUEUE_PROPERTIES, "CL_INVALID_QUEUE_PROPERTIES") 
    CASE(CL_INVALID_COMMAND_QUEUE, "CL_INVALID_COMMAND_QUEUE") 
    CASE(CL_INVALID_HOST_PTR, "CL_INVALID_HOST_PTR") 
    CASE(CL_INVALID_MEM_OBJECT, "CL_INVALID_MEM_OBJECT") 
    CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR, "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR") 
    CASE(CL_INVALID_IMAGE_SIZE, "CL_INVALID_IMAGE_SIZE") 
    CASE(CL_INVALID_SAMPLER, "CL_INVALID_SAMPLER") 
    CASE(CL_INVALID_BINARY, "CL_INVALID_BINARY") 
    CASE(CL_INVALID_BUILD_OPTIONS, "CL_INVALID_BUILD_OPTIONS") 
    CASE(CL_INVALID_PROGRAM, "CL_INVALID_PROGRAM") 
    CASE(CL_INVALID_PROGRAM_EXECUTABLE, "CL_INVALID_PROGRAM_EXECUTABLE") 
    CASE(CL_INVALID_KERNEL_NAME, "CL_INVALID_KERNEL_NAME") 
    CASE(CL_INVALID_KERNEL_DEFINITION, "CL_INVALID_KERNEL_DEFINITION") 
    CASE(CL_INVALID_KERNEL, "CL_INVALID_KERNEL") 
    CASE(CL_INVALID_ARG_INDEX, "CL_INVALID_ARG_INDEX") 
    CASE(CL_INVALID_ARG_VALUE, "CL_INVALID_ARG_VALUE") 
    CASE(CL_INVALID_ARG_SIZE, "CL_INVALID_ARG_SIZE") 
    CASE(CL_INVALID_KERNEL_ARGS, "CL_INVALID_KERNEL_ARGS") 
    CASE(CL_INVALID_WORK_DIMENSION, "CL_INVALID_WORK_DIMENSION") 
    CASE(CL_INVALID_WORK_GROUP_SIZE, "CL_INVALID_WORK_GROUP_SIZE") 
    CASE(CL_INVALID_WORK_ITEM_SIZE, "CL_INVALID_WORK_ITEM_SIZE") 
    CASE(CL_INVALID_GLOBAL_OFFSET, "CL_INVALID_GLOBAL_OFFSET") 
    CASE(CL_INVALID_EVENT_WAIT_LIST, "CL_INVALID_EVENT_WAIT_LIST") 
    CASE(CL_INVALID_EVENT, "CL_INVALID_EVENT") 
    CASE(CL_INVALID_OPERATION, "CL_INVALID_OPERATION") 
    CASE(CL_INVALID_GL_OBJECT, "CL_INVALID_GL_OBJECT") 
    CASE(CL_INVALID_BUFFER_SIZE, "CL_INVALID_BUFFER_SIZE") 
    CASE(CL_INVALID_MIP_LEVEL, "CL_INVALID_MIP_LEVEL") 
    CASE(CL_INVALID_GLOBAL_WORK_SIZE, "CL_INVALID_GLOBAL_WORK_SIZE") 
  }
  return NULL; 
}
