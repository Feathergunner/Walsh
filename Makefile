CXX = g++
CXXFLAGS = -std=c++0x -O -c

SRC = main.cpp src/WalshExpansion.cpp src/WalshTransformations.cpp src/BMPWriter.cpp src/MatrixBuilder.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = ohnemakeistallesdoof

%.o: %%.cpp
	$(CXX) $(CXXFLAGS) $^  

all: $(OBJ)
	$(CXX) $^ -o $(EXECUTABLE)

.PHONY clean:
	rm *.o $(EXECUTABLE)
