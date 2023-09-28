# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 17:26:09 by ajakubcz          #+#    #+#              #
#    Updated: 2023/09/28 13:43:32 by hdamitzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = libft/libft.a
LIBMLX = mlx_linux/libmlx.a
DIR_SRCS = srcs/
DIR_PARSING = $(DIR_SRCS)parsing/
DIR_DISPLAY = $(DIR_SRCS)display/
SRCS =	$(DIR_SRCS)main.c \
		$(DIR_SRCS)hook.c \
		$(DIR_SRCS)utils.c \
		$(DIR_SRCS)utils_mlx.c \
		$(DIR_PARSING)parse_file.c \
		$(DIR_PARSING)utils_parse.c \
		$(DIR_PARSING)set_ressource.c \
		$(DIR_PARSING)set_map.c \
		$(DIR_PARSING)verif_map.c \
		$(DIR_PARSING)error_parsing.c \
		$(DIR_DISPLAY)put_minimap.c \
		$(DIR_DISPLAY)put_all_map.c \
		$(DIR_DISPLAY)put_settings.c \
		$(DIR_DISPLAY)put_settings_opti.c \
		$(DIR_DISPLAY)display_windows.c \
		$(DIR_DISPLAY)put_rayon.c \
		$(DIR_DISPLAY)put_recasting.c \
		$(DIR_DISPLAY)put_line.c
		
HEADER = cub3d.h

DIR_OBJS = ./.objs/
OBJS = $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all : mlx_rule libft_rule $(NAME)

$(DIR_OBJS)%.o: %.c $(HEADER) $(LIBFT) $(LIBMLX)
				@mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) -I ./ -I libft2 -I/usr/include -Imlx_linux -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) $(MLXFLAGS) -o $(NAME)

mlx_rule :
	make -C mlx_linux

libft_rule :
	make -C libft

clean : 
		rm -rf $(OBJS) 
		make clean -C mlx_linux
		make clean -C libft

fclean : clean
		rm -rf $(NAME) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re mlx_rule libft_rule
