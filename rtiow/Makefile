CXX = g++
CXXFLAGS = -Wall -g -std=c++11

TARGET = main

all: $(TARGET) run

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.exe

run: 
	./main.exe > image_out.ppm

clean:
	rm main.exe
	rm image_out.ppm