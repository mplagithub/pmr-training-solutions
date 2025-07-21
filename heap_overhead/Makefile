CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := standard_allocations
SRC := standard_allocations.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)