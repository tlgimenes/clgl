#ifndef CLERROR_HPP
#define CLERROR_HPP

#include <CL/cl.h>
#include <stdlib.h>
#include <iostream>

class CLError {
  private:
    int error;
  public:
    static const int cl_success = CL_SUCCESS;
    static const int cl_invalid_buffer_size = CL_INVALID_BUFFER_SIZE ; 
    static const int cl_invalid_host_ptr =  CL_INVALID_HOST_PTR;
    static const int cl_invalid_platform =  CL_INVALID_PLATFORM;
    static const int cl_invalid_value = CL_INVALID_VALUE;
    static const int cl_invalid_device = CL_INVALID_DEVICE;
    static const int cl_invalid_program = CL_INVALID_PROGRAM;
    static const int cl_invalid_binary = CL_INVALID_BINARY;
    static const int cl_invalid_build_options = CL_INVALID_BUILD_OPTIONS;
    static const int cl_invalid_operation = CL_INVALID_OPERATION;
    static const int cl_invalid_context = CL_INVALID_CONTEXT;
    static const int cl_compiler_not_available = CL_COMPILER_NOT_AVAILABLE;
    static const int cl_build_program_failure = CL_BUILD_PROGRAM_FAILURE;
    static const int cl_device_not_available = CL_DEVICE_NOT_AVAILABLE;
    static const int cl_device_not_found = CL_DEVICE_NOT_FOUND;
    static const int cl_out_of_host_memory = CL_OUT_OF_HOST_MEMORY;
    static const int cl_invalid_device_type = CL_INVALID_DEVICE_TYPE;
    static const int cl_mem_object_allocation_failure = CL_MEM_OBJECT_ALLOCATION_FAILURE;

    CLError(int errorCode);
    void printError();

    static void set(cl_int error)
    {
      if(error != CLError::cl_success){
        std::cout << "Oh no ! Impossible Happened !" << std::endl;
        std::cout << "Error Code : " << error << std::endl;
        exit(1);
      }
    }
};

#endif
