/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_settings_opti.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:09:34 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/27 10:51:12 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_cadre_opti(t_cube *data, t_img *img);
void	put_line_cursor_opti(t_cube *data, t_img *img, int height, int type);
void	put_cursor_opti(t_cube *data, t_img *img, int height, int type);

void	put_settings_opti(t_cube *data)
{
	t_img	img;
	
	img.img = mlx_new_image(data->mlx, 610, 460);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	put_cadre_opti(data, &img);
	put_line_cursor_opti(data, &img, 100, SPEED);
	put_line_cursor_opti(data, &img, 250, FOV);
	put_line_cursor_opti(data, &img, 400, M_SPEED);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 700, 300);
	if (data->mode_settings)
	{
		mlx_string_put(data->mlx, data->win, 720, 320 + 16, 0xFFFFFF, "Speed :");
		mlx_string_put(data->mlx, data->win, 720, 470 + 16, 0xFFFFFF, "FOV :");
		mlx_string_put(data->mlx, data->win, 720, 620 + 16, 0xFFFFFF, "Mouse sensibility :");
	}
	mlx_destroy_image(data->mlx, img.img);
}

void	put_cadre_opti(t_cube *data, t_img *img)
{
	int x;
	int y;

	(void) data;
	x = 0;
	while (x < 610)
	{
		y = 0;
		while (y < 460)
		{
			if (y > 0 && y < 460 && ((x > 0 && x < 10) || (x > 600 && x < 610)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (x > 0 && x < 610 && ((y > 0 && y < 10) || (y > 450 && y < 460)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (y > 10 && y < 450 && x > 10 && x < 600)
				my_mlx_pixel_put(img, x, y, my_mlx_pixel_get(&data->all_win, x + 700, y + 300));
			y++;
		}
		x++;
	}
}

void	put_line_cursor_opti(t_cube *data, t_img *img, int height, int type)
{
	int x;
	int y;
	float	dist;
	
	(void) data;
	(void) type;
	x = 50;
	while (x < 560)
	{
		y = height - 10;
		while (y < height + 10)
		{
			dist = sqrt(pow((x - 60), 2) + pow((y - height), 2));
			if (dist < 10)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			dist = sqrt(pow((x - 550), 2) + pow((y - height), 2));
			if (dist < 10)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			if (x > 60 && x < 550)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			y++;
		}
		x++;
	}
	put_cursor_opti(data, img, height, type);
}

void	put_cursor_opti(t_cube *data, t_img *img, int height, int type)
{
	int		x;
	int		y;
	float	dist;
	
	(void) data;
	(void) type;
	x = 20;
	while (x < 590)
	{
		y = height - 30;
		while (y < height + 30)
		{
			dist = sqrt(pow((x - (data->pos_param[type] - 700)), 2) + pow((y - height), 2));
			if (dist < 30 && dist > 25)
				my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			else if (dist <= 25)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			y++;
		}
		x++;
	}
}