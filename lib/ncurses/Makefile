##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

NAME		=	lib_arcade_ncurses.so

SRC			=	src/ncurses.cpp		\
				object/NCurses.cpp	\

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++

CPPFLAGS	=	-o $(NAME) -I./include -I../../interfaces -I./object -fPIC -lncurses -Wall -Wextra -Werror	

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -shared $(CPPFLAGS) $(OBJ)
			cp -f $(NAME) ../

clean:
			rm -f $(OBJ)

fclean:
			rm -f $(NAME)
			rm -f ../$(NAME)

re:			fclean all

.PHONY:		all clean fclean re