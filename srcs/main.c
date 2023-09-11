/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:27:29 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/11 21:58:39 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initiate_data(t_cube *data);

void	put_square(int x, int y, t_img *img)
{
	int	i;
	int	j;

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

int	test_move(int x, int y, t_cube *data)
{
	t_img	img;

	if (data->mouse_press)
	{
		img.img = mlx_new_image(data->mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
									&img.line_length, &img.endian);
		put_square(x, y, &img);
		mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
		mlx_destroy_image(data->mlx, img.img);
	}
	return (0);
}

int	test_click(int i, int x, int y, t_cube *data)
{
	(void) i;
	(void) x;
	(void) y;
	data->mouse_press = 1;
	write(2, "click\n", 6);
	return (0);
}

int	test_release(int i, int x, int y, t_cube *data)
{
	(void) i;
	(void) x;
	(void) y;
	data->mouse_press = 0;
	write(2, "relache\n", 8);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	data;

	if (ac != 2)
		return (printf("Not good arguments\n"), 1);
	ft_printf("%d\n", 0xFF00);
	initiate_data(&data);
	data.mlx = mlx_init();
	parse_file(av[1], &data);
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Cub3D!");
	display_windows(&data);
	mlx_hook(data.win, ON_MOUSEMOVE, 1L << 6, test_move, &data);
	mlx_hook(data.win, 4, 1L << 2, test_click, &data);
	mlx_hook(data.win, 5, 1L << 3, test_release, &data);
	init_hook(&data);
	mlx_loop(data.mlx);
}

void	initiate_data(t_cube *data)
{
	// data->north_img.img = NULL;
	// data->south_img.img = NULL;
	// data->east_img.img = NULL;
	// data->west_img.img = NULL;
	data->ceil_color[0] = -1;
	data->floor_color[0] = -1;
	data->mouse_press = 0;
	data->center_north[0] = 0;
	data->center_north[1] = 0;
}
