/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:51:52 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/31 18:54:09 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_circle(t_img *img);
void	put_map(t_img *img, t_cube *data);
void	put_perso(t_img *img);
void	put_pixel(t_img *img, int x, int y, t_cube *data);
char	get_char_of_pos(t_cube *data, int x, int y);
void	get_diff(float diff[2], t_cube *data, int x, int y);
void	put_north(t_img *img, t_cube *data);

void	put_minimap(t_cube *data, t_img *img)
{
	put_circle(img);
	put_map(img, data);
	put_perso(img);
	put_north(img, data);
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
			if (dist > 100 && dist < 103)
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
		y = 160;
		while (y < 180)
		{
			dist = sqrt(pow((x - 110), 2) + pow((y - 170), 2));
			if (dist < 4)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}

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
			if (dist <= 100)
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
	char	c;

	c = get_char_of_pos(data, x, y);
	if (c == '1')
		my_mlx_pixel_put(img, x, y, 0x00666666);
	else if (c == ' ' || c == 0)
		my_mlx_pixel_put(img, x, y, 0x00222222);
	else
		my_mlx_pixel_put(img, x, y, 0x00DDDDDD);
}

char	get_char_of_pos(t_cube *data, int x, int y)
{
	float	diff[2];

	diff[0] = 0;
	diff[1] = 0;
	get_diff(diff, data, x, y);
	if ((diff[1] + data->perso.pix_pos[1] - 170) < 0 || (diff[1] + data->perso.pix_pos[1] - 170) >= data->map.height * 15)
		return (0);
	else if ((diff[0] + data->perso.pix_pos[0] - 110) < 0 || (diff[0] + data->perso.pix_pos[0] - 110) >= data->map.width * 15)
		return (0);
	return (data->map.map[(int)(diff[1] + data->perso.pix_pos[1] - 170) / 15]\
						[(int)(diff[0] + data->perso.pix_pos[0] - 110) / 15]);
}

void	get_diff(float diff[2], t_cube *data, int x, int y)
{
	float	rad;
	float	vec_1[2];
	float	vec_2[2];
	float	point[2];

	vec_1[0] = x - 110;
	vec_1[1] = y - 170;
	rad = data->perso.orientation * (M_PI / 180);
	// printf("%f\n", rad);
	vec_2[0] = vec_1[0] * cosf(rad) - vec_1[1] * sinf(rad);
	vec_2[1] = vec_1[0] * sinf(rad) + vec_1[1] * cosf(rad);
	point[0] = 110 + vec_2[0];
	point[1] = 170 + vec_2[1];
	diff[0] = point[0];
	diff[1] = point[1];
	//printf("diff %f %f %d %d %f %f\n", diff[0], diff[1], x , y, vec_AC[0], vec_AC[1]);
}

void	get_north_pos(float pos[2], t_cube *data, int x, int y)
{
	float	rad;
	float	vec_1[2];
	float	vec_2[2];

	vec_1[0] = x - 110;
	vec_1[1] = y - 110;
	rad = data->perso.orientation * (M_PI / 180);
	vec_2[0] = vec_1[0] * cosf(rad) - vec_1[1] * sinf(rad);
	vec_2[1] = vec_1[0] * sinf(rad) + vec_1[1] * cosf(rad);
	pos[0] = 110 - vec_2[0];
	pos[1] = 110 + vec_2[1];
}

void	put_north(t_img *img, t_cube *data)
{
	int x;
	int y;
	int dist;
	get_north_pos(data->center_north, data, 110, 9);
	// ft_printf("center north : %d %d\n", center_north[0], center_north[1]);
	y = data->center_north[1] - 10;
	while (y < data->center_north[1] + 10)
	{
		x = data->center_north[0] - 10;
		while (x < data->center_north[0] + 10)
		{
			// ft_printf("coords %d %d\n", x, y);
			dist = sqrt(pow((x - data->center_north[0]), 2) + pow((y - data->center_north[1]), 2));
			if (dist <= 9)
			{
				// ft_printf("coords %d %d\n", x, y);
				my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			}
			x++;
		}
		y++;
	}
	//mlx_string_put(data->mlx, img, center_north[0], center_north[1], 0xFF00FF, "NNNNNNNNNNNN");
}
