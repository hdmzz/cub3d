/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:51:52 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/28 20:29:41 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sphere(t_img *img);
void	put_map(t_img *img, t_cube *data);
void	put_perso(t_img *img);
void	put_pixel(t_img *img, int x, int y, t_cube *data);

void	put_minimap(t_cube *data, t_img *img)
{
	(void) data;
	puts("TEST");
	put_sphere(img);
	put_map(img, data);
	put_perso(img);
}

void	put_sphere(t_img *img)
{
	int		x;
	int		y;
	float	dist;
	
	x = 0;
	while (x < 220)
	{
		y = 0;
		while (y < 220)
		{
			dist = sqrt(pow((x - 110), 2) + pow((y - 110), 2));
			if (dist > 96 && dist < 99)
				my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

void	put_perso(t_img *img)
{
	int		x;
	int		y;
	float	dist;
	
	x = 100;
	while (x < 120)
	{
		y = 150;
		while (y < 170)
		{
			dist = sqrt(pow((x - 110), 2) + pow((y - 160), 2));
			if (dist < 4)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}

// void	put_map(t_img *img, t_cube *data)
// {
// 	int		x;
// 	int		y;
// 	float	dist;
	
// 	x = -50; // 110 - 160 || 160 est la plus grande distance entre le perso et le bord en haut du cercle
// 	while (x < 110 + 160)
// 	{
// 		y = 0;
// 		while (y < 160 + 160)
// 		{
// 			ft_printf("coords %d %d\n", x, y);
// 			dist = sqrt(pow((x - 110), 2) + pow((y - 110), 2));
// 			if (dist <= 96)
// 				put_pixel(img, x, y, data);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	put_map(t_img *img, t_cube *data)
{
	int		x;
	int		y;
	float	dist;
	
	x = 0;
	while (x < 220 && x < data->map.width * 12)
	{
		y = 0;
		while (y < 220 && y < data->map.height * 12)
		{
			// ft_printf("coords %d %d\n", x, y);
			dist = sqrt(pow((x - 110), 2) + pow((y - 110), 2));
			if (dist <= 96)
				put_pixel(img, x, y, data);
			y++;
		}
		x++;
	}
}

void	put_pixel(t_img *img, int x, int y, t_cube *data)
{
	(void) data;
	if (data->map.map[y / 12][x / 12] == '1')
                my_mlx_pixel_put(img, x, y, 0x00666666);
	else if (data->map.map[y / 12][x / 12] == ' ')
		my_mlx_pixel_put(img, x, y, 0x00222222);
	else
		my_mlx_pixel_put(img, x, y, 0x00DDDDDD);
}
