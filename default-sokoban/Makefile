##
## EPITECH PROJECT, 2022
## B-PSU-100-RUN-1-1-bssokoban-pierre-alexandre.grosset
## File description:
## Makefile
##

CC 	= 	gcc

NAME =	my_sokoban

SRC	=	src/inits.c \
		src/loop.c \
		src/main.c \
		src/my_include.c \
		src/process.c \
		src/validity.c

INCLUDE = 	./

CFLAGS 	= 	-W -Wall -Wextra

NCURSESLIB	=	-lncurses

all:
	gcc -o $(NAME) $(SRC) $(SRCINCLUDE) $(CFLAGS) $(NCURSESLIB)

clean:
	rm -f a.out
	rm -f $(NAME)
	rm -f $(OBJ)

fclean: clean

re: fclean all
