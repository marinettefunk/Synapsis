SYNAPSIS: welcome.o main.o profile.o menu.o formatting.o files.o chat.o
	g++ -std=c++17 welcome.o main.o profile.o menu.o formatting.o files.o chat.o -o SYNAPSIS

welcome.o: welcome.cpp welcome.h formatting.h
	g++ -c -std=c++17 welcome.cpp

profile.o: profile.cpp profile.h formatting.h welcome.h menu.h
	g++ -c -std=c++17 profile.cpp

main.o: main.cpp welcome.h profile.h menu.h
	g++ -c -std=c++17 main.cpp

menu.o: menu.cpp menu.h profile.h files.h chat.h
	g++ -c -std=c++17 menu.cpp

formatting.o: formatting.cpp formatting.h welcome.h menu.h
	g++ -c -std=c++17 formatting.cpp

files.o: files.cpp files.h profile.h formatting.h welcome.h menu.h
	g++ -c -std=c++17 files.cpp

chat.o: chat.cpp chat.h files.h profile.h formatting.h welcome.h menu.h
	g++ -c -std=c++17 chat.cpp

clean:
	rm -f *.o SYNAPSIS

all: SYNAPSIS
	./SYNAPSIS