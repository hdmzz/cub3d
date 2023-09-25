/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:27:29 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/25 18:08:05 by ajakubcz         ###   ########.fr       */
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

int move_settings(int x, int y, t_cube *data)
{
	(void) y;
	if (data->mouse_press && data->type_param_click != -1)
	{
		if (x < 760)
		{
			if (data->pos_param[data->type_param_click] != 760)
			{
				data->pos_param[data->type_param_click] = 760;
				put_settings_opti(data);
			}
		}
		else if (x > 1250)
		{
			if (data->pos_param[data->type_param_click] != 1250)
			{
				data->pos_param[data->type_param_click] = 1250;
				put_settings_opti(data);
			}
		}
		else
		{
			data->pos_param[data->type_param_click] = x;
			put_settings_opti(data);
		}
		if (data->type_param_click == FOV)
		{
			data->value_param[FOV] = (data->pos_param[FOV] - 760) * (110 - 30) / (1250 - 760) + 30;
			printf("fov : %d\n", data->value_param[FOV]);
		}
	}
	return (0); 	
}

int	test_click(int button, int x, int y, t_cube *data)
{
	(void) x;
	(void) y;
	(void) button;
	data->mouse_press = 1;
	if (data->mouse_press && x > 730 && x < 1280)
	{
		if (y > 400 - 30 && y < 400 + 30)
			data->type_param_click = SPEED;
		if (y > 550 - 30 && y < 550 + 30)
			data->type_param_click = FOV;
		if (y > 700 - 30 && y < 700 + 30)
			data->type_param_click = M_SPEED;
		move_settings(x, y, data);
	}
	write(2, "click\n", 6);
	return (0);
}

int	test_release(int button, int x, int y, t_cube *data)
{
	(void) x;
	(void) y;
	(void) button;
	
	
	// if (data->type_param_click == FOV)
	// 	data->value_param[FOV] = (data->pos_param[FOV] - 760) * (110 - 30) / (1250 - 760);
	// printf("");
	if (data->type_param_click == FOV)
		display_windows(data);
	data->type_param_click = -1;
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
	mlx_hook(data.win, ON_MOUSEMOVE, 1L << 6, move_settings, &data);
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
	data->mode_full_map = 0;
	data->mode_settings = 0;
	data->type_param_click = -1;
	data->pos_param[SPEED] = 1000;
	data->pos_param[FOV] = 1000;
	data->pos_param[M_SPEED] = 1000;
	data->value_param[FOV] = 60;
}
