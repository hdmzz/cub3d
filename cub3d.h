/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:05:19 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/26 20:30:14 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE_TILE 100

# include <fcntl.h> //open
# include <unistd.h> //close et sleep
# include <mlx.h>
# include <stdio.h>
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include "libft/libft.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	NO,
	SO,
	WE,
	EA,
	F,
	C	
};

typedef struct s_map {
	char	**map;
	int		height;
	int		width;
}				t_map;

typedef struct s_point {
	int	x;
	int	y;
}				t_point;

typedef struct s_perso {
	t_point	*pos;
	int 	orientation;
}				t_perso;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_cube {
	void	*mlx;
	void	*win;
	t_map	map;
	t_perso	perso;
	t_img	north_img;
	t_img	south_img;
	t_img	east_img;
	t_img	west_img;
	int		ceil_color[3];
	int		floor_color[3];
	int		can_move;
}				t_cube;

//utils.c
int	ft_same_str(char *s1, char *s2);

//PARSING
//parse_file.c
void parse_file(char *name_file, t_cube *data);

//utils_parse.c
int	get_identifier(char *line);

//set_ressource.c
void set_ressource(int fd, t_cube *data);

//set_map.c
void set_map(int fd, char *name_file, t_cube *data);

#endif
