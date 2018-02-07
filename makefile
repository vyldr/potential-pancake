LFLAGS = -lGL -lglut -lGLU

# vars for the backup feature
PACKAGE   = backup
VERSION   = ` date +"%Y%m%d_%H%M%S" `
ARCHIVE   = $(PACKAGE)-$(VERSION)
PRGMNAME  = game

# Programs:
#    $(PRGMNAME):         The game executable

bin/$(PRGMNAME): build/game.o build/uiInteract.o build/uiDraw.o build/mapgen.o build/algorithms.o build/chvar.o build/tile.o build/character.o
	g++ -g -o bin/$(PRGMNAME) build/* $(LFLAGS)



build/game.o: src/game.cpp src/include/game.h src/include/uiDraw.h src/include/uiInteract.h src/include/mapgen.h src/include/algorithms.h src/include/chvar.h src/include/tile.h src/include/character.h src/include/task.h src/include/item.h src/include/definitions.h
	g++ -g -o build/game.o -c src/game.cpp

build/uiInteract.o: src/uiInteract.cpp src/include/uiInteract.h src/include/definitions.h
	g++ -g -o build/uiInteract.o -c src/uiInteract.cpp

build/uiDraw.o: src/uiDraw.cpp src/include/uiDraw.h src/include/definitions.h
	g++ -g -o build/uiDraw.o -c src/uiDraw.cpp

build/mapgen.o: src/mapgen.cpp src/include/mapgen.h src/include/definitions.h
	g++ -g -o build/mapgen.o -c src/mapgen.cpp

build/chvar.o: src/chvar.cpp src/include/chvar.h src/include/definitions.h
	g++ -g -o build/chvar.o -c src/chvar.cpp

build/tile.o: src/tile.cpp src/include/tile.h src/include/game.h src/include/uiDraw.h src/include/definitions.h
	g++ -g -o build/tile.o -c src/tile.cpp

build/character.o: src/character.cpp src/include/character.h src/include/game.h src/include/uiDraw.h src/include/task.h src/include/definitions.h
	g++ -g -o build/character.o -c src/character.cpp

build/algorithms.o: src/algorithms.cpp src/include/algorithms.h src/include/tile.h src/include/definitions.h
	g++ -g -o build/algorithms.o -c src/algorithms.cpp

# General rules

clean:
	rm bin/$(PRGMNAME) build/*.o

all:
	bin/$(PRGMNAME)

go:
	make && bin/$(PRGMNAME)

debug:
	make && gdb bin/$(PRGMNAME)

everything:
	make clean; make go;