##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

NAME		=	arcade

SRC			=	src/arcade.cpp			\
				src/load_filedir.cpp	\
				src/launch_game.cpp		\
				src/menu_name.cpp		\
				src/menu_display.cpp	\
				src/score_page.cpp		\
				object/ArcadeData.cpp	\
				object/Error.cpp		\

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++

CPPFLAGS	=	-o $(NAME) -I./include -I./object -I./interfaces -I./lib/ncurses/object -ldl -Wall -Wextra -g3

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CPPFLAGS) $(OBJ)
			make -C games/pacman
			make -C games/nibbler
			make -C lib/libcaca
			make -C lib/ncurses
			make -C lib/sfml

core:		$(OBJ)
			$(CC) $(CPPFLAGS) $(OBJ)

games:
			make -C games/pacman
			make -C games/nibbler

graphicals:
			make -C lib/libcaca
			make -C lib/ncurses
			make -C lib/sfml

clean:
			rm -f $(OBJ)
			make clean -C games/pacman
			make clean -C games/nibbler
			make clean -C lib/libcaca
			make clean -C lib/ncurses
			make clean -C lib/sfml

fclean:		clean
			rm -f $(NAME)
			make fclean -C games/pacman
			make fclean -C games/nibbler
			make fclean -C lib/libcaca
			make fclean -C lib/ncurses
			make fclean -C lib/sfml

re:			fclean all

.PHONY:		all core games graphicals clean fclean re