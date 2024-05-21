CPP=g++
LD=g++



CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf


all: main

main: main.o jeu.o joueur.o batiment.o troupe.o data.o MAP.o MAPfonction.o testmap.o
	$(LD) $(LDFLAGS) main.o jeu.o joueur.o batiment.o troupe.o data.o MAP.o MAPfonction.o testmap.o -o main $(LIBS)

main.o: main.cpp jeu.hpp
	$(CPP) $(CPPFLAGS) -c main.cpp

jeu.o: jeu.cpp joueur.hpp MAP.hpp data.hpp
	$(CPP) $(CPPFLAGS) -c jeu.cpp

joueur.o: joueur.cpp batiment.hpp troupe.hpp data.hpp testmap.hpp
	$(CPP) $(CPPFLAGS) -c joueur.cpp

batiment.o: batiment.cpp troupe.hpp DefParam.hpp data.hpp
	$(CPP) $(CPPFLAGS) -c batiment.cpp

troupe.o: troupe.cpp batiment.hpp joueur.hpp DefParam.hpp data.hpp testmap.hpp
	$(CPP) $(CPPFLAGS) -c troupe.cpp

data.o: data.cpp DefParam.hpp
	$(CPP) $(CPPFLAGS) -c data.cpp

MAP.o: MAP.cpp testmap.hpp data.hpp MAPfonction.hpp
	$(CPP) $(CPPFLAGS) -c MAP.cpp

MAPfonction.o: MAPfonction.cpp
	$(CPP) $(CPPFLAGS) -c MAPfonction.cpp

testmap.o: testmap.cpp data.hpp DefParam.hpp
	$(CPP) $(CPPFLAGS) -c testmap.cpp

clean:
	rm -f *.o main