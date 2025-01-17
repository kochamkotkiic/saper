CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o gra.o plansza.o interfejs.o
EXEC = gra

# kompilacja całego projektu
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# kompilacja main.c
main.o: main.c gra.h plansza.h interfejs.h
	$(CC) $(CFLAGS) -c main.c

# kompilacja gra.c
gra.o: gra.c gra.h plansza.h interfejs.h
	$(CC) $(CFLAGS) -c gra.c

# kompilacja plansza.c
plansza.o: plansza.c plansza.h
	$(CC) $(CFLAGS) -c plansza.c

# kompilacja interfejs.c
interfejs.o: interfejs.c interfejs.h
	$(CC) $(CFLAGS) -c interfejs.c

# usuwanie plików obiektowych i pliku wykonywalnego
clean:
	rm -f $(OBJ) $(EXEC)

# użycie make do czyszczenia i kompilowania
rebuild: clean $(EXEC)

# testowanie z wprowadzonymi danymi
test: $(EXEC)
	echo "100 100 60\n1 1" | ./$(EXEC) -d 4
