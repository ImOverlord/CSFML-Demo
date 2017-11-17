##
## EPITECH PROJECT, 2017
## project_name
## File description:
## Makefile
##
NAME	=	breakout

SRC	=	main.c \
		main_menu.c \
		draw_func.c \
		game_main.c \
		game_over.c

OBJ	=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -g -lm -lc_graph_prog $(OBJ) -o $(NAME)

clean:	
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
