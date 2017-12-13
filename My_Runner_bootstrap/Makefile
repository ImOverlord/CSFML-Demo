##
## EPITECH PROJECT, 2017
## my_hunter
## File description:
## Makefile
##

NAME	=	my_hunter

SRC	=	./src/my_runner.c \
		./src/link.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -pedantic -g3

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc $(CFLAGS) -lc_graph_prog $(OBJ) -o $(NAME)

clean:	
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all