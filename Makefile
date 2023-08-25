# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 21:43:34 by ajakubcz          #+#    #+#              #
#    Updated: 2023/08/23 20:05:34 by ajakubcz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = libft/libft.a
LIBMLX = mlx_linux/libmlx.a
DIR_SRCS = srcs/
SRCS =	$(DIR_SRCS)main.c
		
HEADER = cub3d.h

DIR_OBJS = ./.objs/
OBJS = $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
CC = gcc
CFLAGS = -Wall -Wextra
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all : mlx_rule libft_rule $(NAME)

$(DIR_OBJS)%.o: %.c $(HEADER) $(LIBFT) $(LIBMLX)
				@mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) -I ./ -I libft2 -I/usr/include -Imlx_linux -O3 -c $< -o $@

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
