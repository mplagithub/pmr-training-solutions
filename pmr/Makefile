CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := memory_resource
SRC := memory_resource.cpp

TARGET2 := memory_resource_from_stl
SRC2 := memory_resource_from_stl.cpp

all: $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TARGET2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SRC2)

clean:
	rm -f $(TARGET) $(TARGET2)