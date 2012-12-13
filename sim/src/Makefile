SHELL=/bin/bash
CC=g++
C_FLAGS=-g -c -Wall -O0
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

CL_PATH_ATI=/opt/AMDAPP/include/
CL_PATH_NVIDIA=$(HOME)/NVIDIA_GPU_Computing_SDK/OpenCL/common/inc

INCLUDE_PATH=../include 

all: $(OBJ)

%.o: %.cpp
	if [ -d "$(CL_PATH_ATI)" ]; then \
		$(CC) $(C_FLAGS) -I$(INCLUDE_PATH) -I$(CL_PATH_ATI) $< -o $@; \
	else \
		$(CC) $(C_FLAGS) -I$(INCLUDE_PATH) -I$(CL_PATH_NVIDIA) $< -o $@; \
	fi

clean:
	rm *.o
