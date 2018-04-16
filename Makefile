#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@students.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 16:22:07 by banthony          #+#    #+#              #
#    Updated: 2018/04/16 17:48:59 by banthony         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3D

PATH_SRC = ./src/

PATH_HEAD = ./include/

HEADER_FILE = wolf.h	\

SRC_FILE +=	main.c
SRC_FILE += game.c
SRC_FILE += game_end.c
SRC_FILE += map_creator.c
SRC_FILE += main_menu.c
SRC_FILE += refresh.c
SRC_FILE += draw.c
SRC_FILE += event.c
SRC_FILE += font.c

SRC = $(SRC_FILE:%c=$(PATH_SRC)%c)
INCLUDE = $(HEADER_FILE:%h=$(PATH_HEAD)%h)

OBJ = $(SRC_FILE:.c=.o)
OBJ2 = $(OBJ:%.o=$(PATH_SRC)%.o)

UNAME := $(shell uname)

LIBFT = ./libft

ifeq ($(UNAME), Linux)
MLX_LIB = ./minilibx_linux/
HEAD_DIR = -I ./include -I $(LIBFT) -I ~/minilibx
LIB = -L $(LIBFT) -lft -L MLX_LIB -lmlx -lXext -lX11
FLAGS = -Wall -Wextra -Werror
endif

ifeq ($(UNAME), Darwin)
MLX_LIB = ./minilibx_macos/
HEAD_DIR = -I ./include -I $(LIBFT)
LIB = -L $(LIBFT) -lft -L $(MLX_LIB) -lmlx -framework OpenGL -framework Appkit
FLAGS = -Wall -Wextra -Werror -Weverything
endif

DEBUG = -g

TRASH = Makefile~		\
		./src/*.c~		\
		./include/*.h~	\

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	make -C $(MLX_LIB)
	make -C $(LIBFT)
	gcc $(FLAGS) $(HEAD_DIR) -c $(SRC)
	mv $(OBJ) $(PATH_SRC)
	gcc -o $(NAME) $(OBJ2) $(HEAD_DIR) $(LIB)

debug: $(SRC) $(INCLUDE)
	make debug -C $(LIBFT)
	gcc $(FLAGS) $(HEAD_DIR) -c $(SRC) $(DEBUG)
	mv $(OBJ) $(PATH_SRC)
	gcc -o $(NAME) $(OBJ2) $(HEAD_DIR) $(LIB) $(DEBUG)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ2) $(TRASH)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all
