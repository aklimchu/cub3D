# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/12/04 14:25:19 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Program name
NAME		= cub3D

# Compiler
CC 			= cc
CFLAGS		= -g -ggdb3 -Wall -Wextra -Werror -I $(LIBFT_DIR)
RM			= rm -f
RMDIR		= rm -rf

# MLX42
MLX_PATH	= MLX42/
MLX_NAME	= libmlx42.a
MLX			= $(MLX_PATH)/build/$(MLX_NAME)

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source / OBJ files / Includes
SRC 		=	src/graphics/events.c \
				src/graphics/tools.c \
				src/graphics/tools_2.c \
				src/graphics/draw_cub.c \
				src/graphics/raycasting.c \
				src/parse/parse.c \
				src/parse/parse_line.c \
				src/main.c \
				src/free_and_exit.c \
				src/error.c
OBJ 		= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= obj
INCLUDE		= -I "./inc" -I "./libft/include"

# Rules
all:	libmlx $(NAME)

libmlx: .mlx42

.mlx42:
	@echo "$(YELLOW)Compiling mlx42... $(DEF_COLOR)"
	@touch .mlx42
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_PATH)
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build && make -C $(MLX_PATH)/build -j4				# make mlx42
	@cp MLX42/include/MLX42/MLX42.h MLX42/include/
	@cp MLX42/include/MLX42/MLX42_Int.h MLX42/include/

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Compiling libft... $(DEF_COLOR)"
	@make -C $(LIBFT_DIR) --no-print-directory		# make libft
	@cp $(LIBFT_LIB) $(NAME)	# copy libft to current
	@cp $(MLX) $(NAME)			# copy mlx42 to current
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX) $(INCLUDE) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "$(GREEN)SUCCESS, CUB3D IS READY $(DEF_COLOR)"

clean:
	@echo "$(RED)Deleting object files... $(DEF_COLOR)"
	@$(RMDIR) $(OBJ_DIR) 
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean:		clean
	@echo "$(GREEN)Deleting cub3D... $(DEF_COLOR)"
	@$(RMDIR) $(NAME) $(LIBFT_LIB) $(MLX) .mlx42 $(MLX_PATH)
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)CLEAR $(DEF_COLOR)"

re: 		fclean all

.PHONY: 	all clean fclean re
