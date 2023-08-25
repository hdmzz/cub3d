/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:05:19 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/23 19:19:18 by ajakubcz         ###   ########.fr       */
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

typedef struct s_point {
	int	x;
	int	y;
}				t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_allimg
{
	t_data	perso;
	t_data	all_perso[4][3];
	t_data	ground;
	t_data	wall;
	t_data	item;
	t_data	exit;
}				t_allimg;

typedef struct s_map
{
	char		**map;
	size_t		width;
	size_t		height;
	void		*mlx;
	void		*mlx_win;
	int			nbr_item;
	t_allimg	allimg;
	t_point		pos_perso;
	int			min[2];
	int			max[2];
	int			size_screen[2];
	int			nbr_move;
	int			finish;
}				t_map;

// so_long.c
int		check_colision(int *pos, int add_x, int add_y, t_map *map);
int		close_win(t_map *map);
void	simple_free(t_map *map);

//for_map.c
char	**set_map(char *fd, t_map *map);
void	fill_map(char **cp_map, int x, int y);
char	**copy(t_map *map);

//check_map.c
void	check_close(t_map *map);
void	check_file(char *file, char *type);

//init_all.c
void	first_set(t_map *map);
void	init_all_img(t_allimg *all_img, t_map *map);
void	first_put_img(t_allimg all_img, t_map *map);

//move_perso.c
void	move_pers(t_map *map, int x, int y, void (*dir)\
(t_map *, int, int, int));
void	up(t_map *map, int x, int y, int i);
void	down(t_map *map, int x, int y, int i);
void	left(t_map *map, int x, int y, int i);
void	right(t_map *map, int x, int y, int i);

//move_windows.c
void	go_up(t_map *map, int pos_map[2]);
void	go_down(t_map *map, int pos_map[2]);
void	go_left(t_map *map, int pos_map[2]);
void	go_right(t_map *map, int pos_map[2]);

//move_utils.c
t_data	get_move_perso(int direction, int i, t_data all_perso[4][3]);
void	choose_move(t_map *map, int add_x, int add_y, int pos_map[2]);
void	move_all_window(int pos_map[2], int add_x, int add_y, t_map *map);
void	move_win_hor(t_map *map, t_data *img, int pos_map[2], int side);
void	move_win_ver(t_map *map, t_data *img, int pos_map[2], int side);

//put_image.c
void	put_tile_to_img(t_map *map, t_data *img, t_data *to_img, int point[2]);
void	put_win_to_img(t_map *map, t_data *img, t_data *to_img, int point[2]);
void	put_perso(t_map *map, int add_x, int add_y);
void	put_map(int min[2], int max[2], t_map *map, t_data *img);
void	put_nbr_move(t_map *map);

//put_image2.c
int		set_finish(t_map *map);
void	put_cadre(t_data *img, int size_x, int size_y);

//so_long_utils.c
int		ft_len_int(int i);
void	free_all(char **map);
void	destroy_all_img(t_map *map);
void	set_point(int point[2], int x, int y);
void	print_map(t_map map);

//rename_mlx.c
void	*f_to_img(t_data *data, void *mlx_ptr, char *filename, int size);
char	*get_data(t_data *data);
int		my_mlx_pixel_get(t_data *data, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	new_img_sec(t_data *img, t_map *map, int size_x, int size_y);

#endif
