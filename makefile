main: welcome.o main.o
	g++ -std=c++11 welcome.o main.o -o main

welcome.o: welcome.cpp welcome.h
	g++ -c -std=c++11 welcome.cpp

main.o: main.cpp welcome.h
	g++ -c -std=c++11 main.cpp

clean:
	rm -f *.o main

all: main
	./main