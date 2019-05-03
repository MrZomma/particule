##
## EPITECH PROJECT, 2017
## makefile
## File description:
## makefile
##

SRCS	=	sources/cook.c \

OBJ	=	$(SRCS:%.c=%.o)

NAME	=	part

INCLUDE	=	-I ./include/

SFML	=	-l c_graph_prog -lm

CFLAGS	=	-W -Wall -Wextra $(INCLUDE) -g

all:		$(OBJ)
		gcc -o $(NAME) $(OBJ) $(SFML)

clean:		
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

