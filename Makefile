#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: banthony <banthony@students.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 16:22:07 by banthony          #+#    #+#              #
#    Updated: 2018/07/29 19:19:35 by banthony         ###   ########.fr        #
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
SRC_FILE += bresenham.c
SRC_FILE += event.c
SRC_FILE += font.c
SRC_FILE += utility.c
SRC_FILE += draw_shape.c

SRC = $(SRC_FILE:%c=$(PATH_SRC)%c)
INCLUDE = $(HEADER_FILE:%h=$(PATH_HEAD)%h)

OBJ = $(SRC_FILE:.c=.o)
OBJ2 = $(OBJ:%.o=$(PATH_SRC)%.o)

UNAME := $(shell uname)

LIBFT = ./libft

LIBFT_NAME = -L $(LIBFT) -lft
LIBFT_NAME_SANIT = -L $(LIBFT) -lft_sanit

ifeq ($(UNAME), Linux)
MLX_LIB = ./minilibx_linux/
HEAD_DIR = -I ./include -I $(LIBFT) -I $(MLX_LIB)
LIB = -L $(MLX_LIB) -lmlx -lXext -lX11 -lbsd
FLAGS = -Wall -Wextra -Werror
endif

ifeq ($(UNAME), Darwin)
MLX_LIB = ./minilibx_macos/
HEAD_DIR = -I ./include -I $(LIBFT)
LIB = -L $(MLX_LIB) -lmlx -framework OpenGL -framework Appkit
FLAGS = -Wall -Wextra -Werror -Weverything
endif

DEBUG = -g3 -fsanitize=address

TRASH = Makefile~		\
		./src/*.c~		\
		./include/*.h~	\

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	make -C $(MLX_LIB)
	make -C $(LIBFT)
	gcc $(FLAGS) $(HEAD_DIR) -c $(SRC)
	mv $(OBJ) $(PATH_SRC)
	gcc $(FLAGS) $(OBJ2) $(HEAD_DIR) $(LIBFT_NAME) $(LIB)  -o $(NAME)

debug: $(SRC) $(INCLUDE)
	make -C $(LIBFT) sanit
	gcc $(FLAGS) $(HEAD_DIR) -c $(SRC) $(DEBUG)
	mv $(OBJ) $(PATH_SRC)
	gcc $(FLAGS) $(OBJ2) $(HEAD_DIR) $(LIBFT_NAME_SANIT) $(LIB) -o $(NAME) $(DEBUG)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJ2) $(TRASH)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm ./custom_map*

re: fclean all
