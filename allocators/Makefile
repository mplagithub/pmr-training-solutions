CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := allocator
SRC := allocator.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)