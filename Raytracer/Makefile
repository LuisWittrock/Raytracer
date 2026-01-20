CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g

# Eigen library path (modify as necessary)
EIGEN_INCLUDE := /usr/include/eigen3

SRC     := src
INCLUDE := include

# Add Eigen to the include directories
CXX_FLAGS += -I$(INCLUDE) -I$(EIGEN_INCLUDE)

# Use pkg-config to get OpenCV flags
OPENCV_FLAGS := $(shell pkg-config --cflags --libs opencv4)

# List of source files
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: clean main.exe

main.exe: main.cpp $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(OPENCV_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@ $(OPENCV_FLAGS)

run: all
	./main.exe

clean:
	rm -f *.exe $(OBJECTS)
