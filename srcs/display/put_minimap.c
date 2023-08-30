/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:51:52 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/29 23:06:24 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_circle(t_img *img);
void	put_map(t_img *img, t_cube *data);
void	put_perso(t_img *img);
void	put_pixel(t_img *img, int x, int y, t_cube *data);
char	get_char_of_pos(t_cube *data, int x, int y);
void	get_diff(float diff[2], t_cube *data, int x, int y);

void	put_minimap(t_cube *data, t_img *img)
{
	(void) data;
	float diff[2];
	//puts("TEST");

	diff[0] = 0;
	diff[1] = 0;
	data->perso.orientation = 45;
	get_diff(diff, data, 110,60);
	put_circle(img);
	put_map(img, data);
	put_perso(img);
}

void	put_circle(t_img *img)
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
	

	
	y = 0;
	while (y < 220)
	{
		x = 0;
		while (x < 220)
		{
			// ft_printf("coords %d %d\n", x, y);
			dist = sqrt(pow((x - 110), 2) + pow((y - 110), 2));
			if (dist <= 96)
			{
				// ft_printf("coords %d %d\n", x, y);
				put_pixel(img, x, y, data);
			}
			x++;
		}
		y++;
	}
}

void	put_pixel(t_img *img, int x, int y, t_cube *data)
{

	// data->perso.pix_pos[0] = x * 15;
	// data->perso.pix_pos[1] = y * 15;
	(void) data;
	if (get_char_of_pos(data, x ,y) == '1')
                my_mlx_pixel_put(img, x, y, 0x00666666);
	else if (get_char_of_pos(data, x ,y) == ' ' || get_char_of_pos(data, x ,y) == 0)
		my_mlx_pixel_put(img, x, y, 0x00222222);
	else
		my_mlx_pixel_put(img, x, y, 0x00DDDDDD);
}

char	get_char_of_pos(t_cube *data, int x, int y)
{
	float diff[2];
	// int point[2];
	
	diff[0] = 0;
	diff[1] = 0;
	// get_diff(diff, data, x, y);
	if ((y + data->perso.pix_pos[1] - diff[1] - 160) < 0 || (y + data->perso.pix_pos[1] - diff[1] - 160) >= data->map.height * 15)
		return (0);
	else if ((x + data->perso.pix_pos[0] + diff[0] - 110) < 0 || (x + data->perso.pix_pos[0] + diff[0] - 110) >= data->map.width * 15)
		return (0);
	else 
		return (data->map.map[(int) (y + data->perso.pix_pos[1] - diff[1] - 160) / 15]\
							 [(int) (x + data->perso.pix_pos[0] + diff[0] - 110) / 15]);
}

void	get_diff(float diff[2], t_cube *data, int x, int y)
{
	float rad;
	float hyp;

	hyp = sqrt(pow((x - 110), 2) + pow((y - 160), 2));

	rad = data->perso.orientation * (M_PI / 180);
	diff[1] = cosf(rad) * hyp;
	diff[0] = sinf(rad) * hyp;
	// printf("diff %f %f %f %f %f\n", diff[0], diff[1], cosf(rad), sinf(rad), hyp);
}
