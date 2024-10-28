main: welcome.o main.o profile.o menu.o formatting.o errors.o files.o chat.o calculator.o
	g++ -std=c++11 welcome.o main.o profile.o menu.o formatting.o errors.o files.o chat.o calculator.o -o main

welcome.o: welcome.cpp welcome.h formatting.h
	g++ -c -std=c++11 welcome.cpp

profile.o: profile.cpp profile.h formatting.h welcome.h menu.h
	g++ -c -std=c++11 profile.cpp

main.o: main.cpp welcome.h profile.h menu.h
	g++ -c -std=c++11 main.cpp

menu.o: menu.cpp menu.h errors.h profile.h files.h
	g++ -c -std=c++11 menu.cpp

errors.o: errors.cpp errors.h
	g++ -c -std=c++11 errors.cpp

formatting.o: formatting.cpp formatting.h welcome.h menu.h
	g++ -c -std=c++11 formatting.cpp

files.o: files.cpp files.h
	g++ -c -std=c++11 files.cpp

chat.o: chat.cpp chat.h
	g++ -c -std=c++11 chat.cpp

calculator.o: calculator.cpp calculator.h
	g++ -c -std=c++11 calcolator.cpp

clean:
	rm -f *.o main

all: main
	./main