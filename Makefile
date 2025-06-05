CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror
TARGET = demo.out
SOURCES = Demo.cpp
HEADERS = MyContainer.hpp AscendingOrderIterator.hpp DescendingOrderIterator.hpp SideCrossOrderIterator.hpp ReverseOrderIterator.hpp OrderIterator.hpp MiddleOutOrderIterator.hpp

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

demo: run

clean:
	rm -f $(TARGET)
