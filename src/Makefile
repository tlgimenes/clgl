CC=g++
C_FLAGS=-g -c -Wall -O0
SRC=CLError.cpp CLGL.cpp CLGLLinux.cpp CLGLFactoryLinux.cpp
OBJ=$(SRC:.cpp=.o)
CL_PATH=/opt/AMDAPP/include/
INCLUDE_PATH=../include
  

all: $(OBJ)

%.o: %.cpp
	$(CC) $(C_FLAGS) -I$(INCLUDE_PATH) -I$(CL_PATH) $< -o $@

clean:
	rm *.o
