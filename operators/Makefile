CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := new_delete
SRC := new_delete.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)