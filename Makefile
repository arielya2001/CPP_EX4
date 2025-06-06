CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror

TARGET = demo.out
SOURCES = Demo.cpp
HEADERS = MyContainer.hpp AscendingOrderIterator.hpp DescendingOrderIterator.hpp SideCrossOrderIterator.hpp ReverseOrderIterator.hpp OrderIterator.hpp MiddleOutOrderIterator.hpp

MAIN_TARGET = main.out
MAIN_SOURCE = Main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

demo: run

main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SOURCE) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) $(MAIN_SOURCE)

clean:
	rm -f $(TARGET) $(MAIN_TARGET)
