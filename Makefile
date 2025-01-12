CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o gra.o plansza.o interfejs.o
EXEC = gra

# Kompilacja całego projektu
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Kompilacja pliku main.c
main.o: main.c gra.h plansza.h interfejs.h
	$(CC) $(CFLAGS) -c main.c

# Kompilacja pliku gra.c
gra.o: gra.c gra.h plansza.h interfejs.h
	$(CC) $(CFLAGS) -c gra.c

# Kompilacja pliku plansza.c
plansza.o: plansza.c plansza.h
	$(CC) $(CFLAGS) -c plansza.c

# Kompilacja pliku interfejs.c
interfejs.o: interfejs.c interfejs.h
	$(CC) $(CFLAGS) -c interfejs.c

# Usuwanie plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(OBJ) $(EXEC)

# Użycie make do czyszczenia i kompilowania
rebuild: clean $(EXEC)
