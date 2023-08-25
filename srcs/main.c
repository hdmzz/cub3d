/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:01:26 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/23 20:19:12 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		can_move;
}				t_vars;

void	put_square(int x, int y, t_data *img)
{
	int i;
	int j;

	i = x - 25;
	while (i < x + 25)
	{
		j = y - 25;
		while (j < y + 25)
		{
			my_mlx_pixel_put(img, i, j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int test_move(int x, int y, t_vars *vars)
{
	t_data	img;
	
	if (vars->can_move)
	{
		img.img = mlx_new_image(vars->mlx, 1020, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
		put_square(x, y, &img);
		mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
		mlx_destroy_image(vars->mlx, img.img);
	}
}

int test_click(int i, int x, int y, t_vars *vars)
{
	vars->can_move = 1;
	write(1, "click\n", 6);
}

int test_release(int i, int x, int y, t_vars *vars)
{
	vars->can_move = 0;
	write(1, "relache\n", 8);
}

int	main(void)
{
	t_vars	vars;

	vars.can_move = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1020, 1080, "Hello world!");
	// img.img = mlx_new_image(mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 							&img.endian);
	// put_square(&img);
	// //my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(vars.win, ON_MOUSEMOVE, 1L<<6, test_move, &vars);
	mlx_hook(vars.win, 4, 1L<<2, test_click, &vars);
	mlx_hook(vars.win, 5, 1L<<3, test_release, &vars);
	mlx_loop(vars.mlx);
}
