CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := allocator
SRC := allocator.cpp

TARGET2 := std_allocator
SRC2 := std_allocator.cpp

all: $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TARGET2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SRC2)

clean:
	rm -f $(TARGET) $(TARGET2)