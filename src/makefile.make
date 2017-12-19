LIB      = -ldl -lglfw3 -pthread -lGLEW -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11
STANDARD = -std=c++11
LIBLOCATION = -L /usr/local/lib/ -L /usr/lib/x86_64-linux-gnu/
CPP = ./main.cpp ./ShaderLoader.cpp ./FileLoader.cpp ./Cube.cpp ./Plane.cpp ./Controls.cpp ./Graphics.cpp 

all: ./main.cpp
	g++ $(LIBLOCATION) $(STANDARD) -Wall -g -o Driver $(CPP) $(LIB)