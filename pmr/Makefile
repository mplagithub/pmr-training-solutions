CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := memory_resource
SRC := memory_resource.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)