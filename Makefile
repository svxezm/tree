CXX = clang++
CXXFLAGS = -std=c++23 -Wall
TARGET = program
SOURCE = main.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: all
	./$(TARGET) && rm -f $(TARGET)

clean:
	rm -f $(TARGET)
