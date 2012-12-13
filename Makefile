CC=g++
SRC=$(wildcard *.cpp)
C_FLAGS=-g -Wall -O0

OBJ=clgl/src/*.o window/src/*.o sim/src/*.o

LIB_PATH_ATI=/opt/AMDAPP/lib/x86_64
LIB_PATH_NVIDIA=$(HOME)/NVIDIA_GPU_Computing_SDK/OpenCL/common/lib

LIBS=-lOpenCL -lGL -lGLU -lglut -lGLEW
INCLUDE_PATH=-Iclgl/include/ -Iwindow/include -Isim/include

CL_PATH_ATI=/opt/AMDAPP/include/
CL_PATH_NVIDIA=$(HOME)/NVIDIA_GPU_Computing_SDK/OpenCL/common/inc

OUTPUT=GravSim

all:
	cd clgl; make
	cd window; make
	cd sim; make
	if [ -d "/opt/AMDAPP/include/" ]; then \
		make ati; \
	else \
		make nvidia; \
	fi

ati:
	$(CC) $(C_FLAGS) -L$(LIB_PATH_ATI) -I$(CL_PATH_ATI) $(INCLUDE_PATH) $(SRC) $(OBJ) -o $(OUTPUT) $(LIBS)

nvidia:
	$(CC) $(C_FLAGS) -L$(LIB_PATH_NVIDIA) -I$(CL_PATH_NVIDIA) $(INCLUDE_PATH) $(SRC) $(OBJ) -o $(OUTPUT) $(LIBS)

clean:
	cd clgl; make clean
	cd window; make clean
	cd sim; make
	rm $(OUTPUT)
