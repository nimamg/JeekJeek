OBJECTS = notification.o comment.o jeek.o user.o network.o interface.o main.o

all: a.out

a.out: $(OBJECTS)
	g++ $(OBJECTS)

notification.o: notification.cpp
	g++ -c notification.cpp

comment.o: comment.cpp
	g++ -c comment.cpp

jeek.o: jeek.cpp
	g++ -c jeek.cpp

user.o: user.cpp
	g++ -c user.cpp

network.o: network.cpp
	g++ -c network.cpp

interface.o: interface.cpp
	g++ -c interface.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f $(OBJECTS) a.out