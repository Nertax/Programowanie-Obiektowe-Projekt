CC=g++
CFLAGS=-Wall -Wextra -I/home/daniel/Pobrane/git-sfml-2.4/SFML/include
OBJ=main.o map.o player.o obstacle.o game.o enemy.o

danielGame: $(OBJ)
	$(CC) -o danielGame $^ -L/home/daniel/Pobrane/sfml-bin2/lib -lsfml-graphics -lsfml-window -lsfml-system
	
#	$(CC) -o danielGame $^ -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) 

clean:
	rm -f *.o


