#variables
OBG_S 	=src/main.c  src/game.c
OBG_N 	=XO
cc			=g++
CFLAGS	=-w -o2
LFLAGS	=-lSDL -lSDL_image
#-lSDL_mixer -lSDL_ttf

all:$(OBG_S)
	$(cc) $(OBG_S) $(CFLAGS) $(LFLAGS) -o $(OBG_N);./XO

out:
	./XO
