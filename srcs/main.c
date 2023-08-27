/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:01:26 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/27 19:14:42 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(int x, int y, t_img *img)
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int test_move(int x, int y, t_cube *data)
{
	t_img	img;
	
	if (data->can_move)
	{
		img.img = mlx_new_image(data->mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
		put_square(x, y, &img);
		mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
		mlx_destroy_image(data->mlx, img.img);
	}
	return (0);
}

int test_click(int i, int x, int y, t_cube *data)
{
	(void) i;
	(void) x;
	(void) y;
	data->can_move = 1;
	write(2, "click\n", 6);
	return (0);
}

int test_release(int i, int x, int y, t_cube *data)
{
	(void) i;
	(void) x;
	(void) y;
	data->can_move = 0;
	write(2, "relache\n", 8);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	data;
	
	if (ac != 2)
		return (printf("not good arguments\n"), 1);
	parse_file(av[1], &data);
	data.can_move = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Cub3D!");
	put_minimap(&data);
	mlx_hook(data.win, ON_MOUSEMOVE, 1L<<6, test_move, &data);
	mlx_hook(data.win, 4, 1L<<2, test_click, &data);
	mlx_hook(data.win, 5, 1L<<3, test_release, &data);
	mlx_loop(data.mlx);
}
