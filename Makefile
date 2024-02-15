CC=gcc
CFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=src/sokoban.c  src/affichage.c src/deplacement.c src/niveau_fichier.c src/timer.c ./src/gestion_menu.c ./src/score.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main
.PHONY : clean
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -rf $(OBJETS) $(EXECUTABLE)
