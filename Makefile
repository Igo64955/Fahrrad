CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGET   = fahrrad_kalkulator

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)
