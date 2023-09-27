/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:38:18 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/27 10:29:08 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_opacity(t_img *img);
void	put_cadre(t_img *img);
void	put_line_cursor(t_cube *data, t_img *img, int height, int type);
void	put_cursor(t_cube *data, t_img *img, int height, int type);


void	put_settings(t_cube *data, t_img *img)
{
	(void) data;
	put_opacity(img);
	put_cadre(img);
	put_line_cursor(data, img, 400, SPEED);
	put_line_cursor(data, img, 550, FOV);
	put_line_cursor(data, img, 700, M_SPEED);
}

// void	put_settings_opti(t_cube *data, t_img *img)
// {
// 	t_img	img2;
// 	int point[2];
	
// 	// puts("a");
// 	img2.img = mlx_new_image(data->mlx, 1920, 1080);
// 	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length,
// 								&img2.endian);
// 	// puts("b");
// 	put_cadre(&img2);
// 	put_line_cursor(data, &img2, 400, SPEED);
// 	put_line_cursor(data, &img2, 550, FOV);
// 	put_line_cursor(data, &img2, 700, M_SPEED);
// 	// puts("c");
// 	point[0] = 0;
// 	point[1] = 0;
// 	put_img_to_img(data, &img2, img, point);
// 	mlx_destroy_image(data->mlx, img2.img);
// 	mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
// }

void	put_opacity(t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			my_mlx_pixel_put(img, x, y, ft_opacity(my_mlx_pixel_get(img, x, y), 0.5));
			y++;
		}
		x++;
	}
}

void	put_cadre(t_img *img)
{
	int x;
	int y;

	x = 700;
	while (x < 1310)
	{
		y = 300;
		while (y < 760)
		{
			if (y > 300 && y < 760 && ((x > 700 && x < 710) || (x > 1300 && x < 1310)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (x > 700 && x < 1310 && ((y > 300 && y < 310) || (y > 750 && y < 760)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (y >= 310 && y <= 750 && x >= 710 && x <= 1300)
				my_mlx_pixel_put(img, x, y, ft_opacity(my_mlx_pixel_get(img, x, y), 0.6));
			y++;
		}
		x++;
	}
}

void	put_line_cursor(t_cube *data, t_img *img, int height, int type)
{
	int x;
	int y;
	float	dist;
	
	(void) data;
	(void) type;
	x = 750;
	while (x < 1260)
	{
		y = height - 10;
		while (y < height + 10)
		{
			dist = sqrt(pow((x - 760), 2) + pow((y - height), 2));
			if (dist < 10)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			dist = sqrt(pow((x - 1250), 2) + pow((y - height), 2));
			if (dist < 10)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			if (x > 760 && x < 1250)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			y++;
		}
		x++;
	}
	put_cursor(data, img, height, type);
}

void	put_cursor(t_cube *data, t_img *img, int height, int type)
{
	int x;
	int y;
	float	dist;
	
	(void) data;
	(void) type;
	x = 720;
	while (x < 1290)
	{
		y = height - 30;
		while (y < height + 30)
		{
			dist = sqrt(pow((x - data->pos_param[type]), 2) + pow((y - height), 2));
			if (dist < 30 && dist > 25)
				my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			else if (dist <= 25)
				my_mlx_pixel_put(img, x, y, 0x00888888);
			y++;
		}
		x++;
	}
}
