/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:05:19 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/27 10:45:05 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE_TILE 100

# include <math.h>
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
	SPEED,
	FOV,
	M_SPEED	
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
	int		pos[2];
	float		pix_pos[2];
	float	vect_dir[2];
	float	front_vect[2];
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

typedef struct s_param
{
	float	move_speed;
	float	fov;
	float	mouse_speed;
}				t_param;


typedef struct	s_cube 
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	all_win;
	t_perso	perso;
	t_img	north_img;
	t_img	south_img;
	t_img	east_img;
	t_img	west_img;
	t_param	settings;
	int		wall_face;
	int		mode_full_map;
	int		mode_settings;
	float	coli_point[2];
	int		ceil_color[3];
	int		floor_color[3];
	int		mouse_press;
	int		type_param_click;
	int		value_param[3];
	int		pos_param[3];
	int		key_press[6];
	float	center_north[2];
}				t_cube;

//main.c

//hook.c
void	init_hook(t_cube *data);

//utils.c
int		ft_same_str(char *s1, char *s2);
int		colision(t_cube *data);

//utils_mlx.c
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
int		my_mlx_pixel_get(t_img *img, int x, int y);
void	put_img_to_img(t_cube *data, t_img *img, t_img *to_img, int point[2]);
void	*f_to_img(t_img *data, void *mlx_ptr, char *filename, int size);
int	ft_opacity(int color, double opacity);

//PARSING
//parse_file.c
void parse_file(char *name_file, t_cube *data);

//utils_parse.c
int	get_identifier(char *line, t_cube *data);

//set_ressource.c
void set_ressource(int fd, t_cube *data);

//set_map.c
void set_map(int fd, char *name_file, t_cube *data);
void	print_map(char **map); //TO DELETE

//verif_map.c
void	verif_map(t_cube *data);


//DISPLAY
//put_minimap.c
void	put_minimap(t_cube *data, t_img *img);

//put_all_map.c
void	put_all_map(t_cube *data, t_img *img);

//put_settings.c
void	put_settings(t_cube *data, t_img *img);
void	put_settings_opti(t_cube *data);

//display_windows.c
void	display_windows(t_cube *data);

//put_rayon.c
void	put_rayon(t_cube *data, t_img *img);

//put_recating.c
void	put_recasting(t_cube *data, t_img *img);

//put_line.c
void	put_line(int num_rayon, double dist ,t_cube *data, t_img *img);

#endif
