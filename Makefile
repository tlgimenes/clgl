CC=g++
SRC=$(wildcard *.cpp)
OBJ=src/*.o
C_FLAGS=-g -Wall -O0
LIB_PATH=/opt/AMDAPP/lib/x86_64
LIBS=-lOpenCL -lGL -lGLU -lglut -lGLEW
INCLUDE_PATH=include/
CL_PATH=/opt/AMDAPP/include/

all:
	cd src; make

clean:
	cd src; make clean
