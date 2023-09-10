/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_recasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:43:41 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/10 22:37:51 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_dist(int num_rayon, float rotation, t_cube *data, t_img *img);
void get_precise_dist(t_cube *data, float point[2]);
double get_angle(int num_rayon, float rotation, t_cube *data);
void	put_line(int num_rayon, double dist ,t_cube *data, t_img *img);
int good_char(char c);
int col_rayon(t_cube *data, float point[2], int preci);

void	put_sphere2(t_img *img, float point[2])
{
	int		x;
	int		y;
	float	dist;

	x = point[0] - 5;
	while (x < point[0] + 5)
	{
		y = point[1] - 5;
		while (y < point[1] + 5)
		{
			dist = sqrt(pow((x - point[0]), 2) + pow((y - point[1]), 2));
			if (dist < 2)
				my_mlx_pixel_put(img, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	put_recasting(t_cube *data, t_img *img)
{
	float rotation;
	int num_rayon;

	num_rayon = 0;
	rotation = data->perso.orientation - 30;
	if (rotation < 0)
		rotation += 360;
	while (num_rayon < 1920)
	{		
		put_line(num_rayon, get_dist(num_rayon, rotation, data, img), data, img);
		rotation += (float) 60 / 1920;
		num_rayon++;
		if (rotation >= 360)
			rotation -= 360;
	}
}
void	set_wall_face(t_cube *data, float point[2])
{
	if (!good_char(data->map.map[(int) (point[1] + 0.01) / 15][(int) point[0] / 15]))
		data->wall_face = SO;
	else if (!good_char(data->map.map[(int) (point[1] - 0.01) / 15][(int) point[0] / 15]))
		data->wall_face = NO;
	else if (!good_char(data->map.map[(int) point[1] / 15][(int) (point[0] + 0.01) / 15]))
		data->wall_face = EA;
	else if (!good_char(data->map.map[(int) point[1] / 15][(int) (point[0] - 0.01) / 15]))
		data->wall_face = WE;	
	else
		data->wall_face = -1;
}

double get_dist(int num_rayon, float rotation, t_cube *data, t_img *img)
{
	int		basic_vect[2];
	float	point[2];
	double	rad;
	long double	hyp;
	
	(void) img;
	point[0] = data->perso.pix_pos[0];
	point[1] = data->perso.pix_pos[1];
	basic_vect[0] = 0;
	basic_vect[1] = 1;
	rad = rotation * (M_PI / 180);
	data->perso.front_vect[0] = basic_vect[0] * cosf(rad) + basic_vect[1] * sinf(rad);
	data->perso.front_vect[1] = basic_vect[0] * sinf(rad) - basic_vect[1] * cosf(rad);
	// printf("x : %f y : %f\n", data->perso.front_vect[0], data->perso.front_vect[1]);
	get_precise_dist(data, point);
	set_wall_face(data, point);
	// put_sphere2(img, point);
	// printf("%Lf %Lf %f\n", point[0], point[1], pow((data->perso.pix_pos[0] - point[0]), 2) + pow((data->perso.pix_pos[1] - point[1]), 2));
	hyp = sqrtl(pow((data->perso.pix_pos[0] - point[0]), 2) + pow((data->perso.pix_pos[1] - point[1]), 2));
	rad = get_angle(num_rayon, rotation, data) * (M_PI / 180);
	// printf("hyp : %Lf\n", hyp);
	return ((double) hyp * cosf(rad));
}

// void get_precise_dist(t_cube *data, float point[2])
// {
// 	while (data->map.map[(int) point[1] / 15][(int) point[0] / 15] != '1')
// 	{
// 		point[0] += data->perso.front_vect[0];
// 		point[1] += data->perso.front_vect[1];
// 	}
// 	while (data->map.map[(int) point[1] / 15][(int) point[0] / 15] == '1')
// 	{
// 		point[0] -= data->perso.front_vect[0] / 10;
// 		point[1] -= data->perso.front_vect[1] / 10;
// 	}
// 	while (data->map.map[(int) point[1] / 15][(int) point[0] / 15] != '1')
// 	{
// 		point[0] += data->perso.front_vect[0] / 100;
// 		point[1] += data->perso.front_vect[1] / 100;
// 	}
// 	while (data->map.map[(int) point[1] / 15][(int) point[0] / 15] == '1')
// 	{
// 		point[0] -= data->perso.front_vect[0] / 500;
// 		point[1] -= data->perso.front_vect[1] / 500;
// 	}
// 	set_wall_face(data, point);
// }

void get_precise_dist(t_cube *data, float point[2])
{
	while (!col_rayon(data, point, 1))
	{
		point[0] += data->perso.front_vect[0];
		point[1] += data->perso.front_vect[1];
	}
	while (!col_rayon(data, point, 10))
	{
		point[0] += data->perso.front_vect[0] / 10;
		point[1] += data->perso.front_vect[1] / 10;
	}
	while (!col_rayon(data, point, 100))
	{
		point[0] += data->perso.front_vect[0] / 100;
		point[1] += data->perso.front_vect[1] / 100;
	}
	while (!col_rayon(data, point, 500))
	{
		point[0] += data->perso.front_vect[0] / 500;
		point[1] += data->perso.front_vect[1] / 500;
	}
}

int col_rayon(t_cube *data, float point[2], int preci)
{
	if (!good_char(data->map.map[(int) (point[1] + (data->perso.front_vect[1] / preci)) / 15][(int) point[0] / 15]))
		return (1);
	if (!good_char(data->map.map[(int) point[1] / 15][(int) (point[0] + (data->perso.front_vect[0] / preci)) / 15]))
		return (1);
	if (!good_char(data->map.map[(int) (point[1] + (data->perso.front_vect[1] / preci))  / 15][(int) (point[0] + (data->perso.front_vect[0] / preci)) / 15]))
		return (1);
	return (0);
}

int good_char(char c)
{
	if (c == '1' || c == ' ')
		return (0);
	return (1);
}

double get_angle(int num_rayon, float rotation, t_cube *data)
{
	if (num_rayon < 1920 / 2 && rotation > data->perso.orientation)
		return (360 - rotation + data->perso.orientation);
	else if(num_rayon < 1920 / 2)
			return (data->perso.orientation - rotation);
	else if (num_rayon >= 1920 / 2 && rotation < data->perso.orientation)
		return (360 - data->perso.orientation + rotation);
	else if(num_rayon >= 1920 / 2)
			return (rotation - data->perso.orientation);
	return (0);
}

void	put_line(int num_rayon, double dist ,t_cube *data, t_img *img)
{
	int i;

	i = 0;
	(void) num_rayon;
	(void) data;
	(void) img;
	// printf("dist : %f\n", dist);
	double height = (double) (1 / dist) * 2000;
	while (i < 1080)
	{
		if (i > (1080 / 2) - height && i < (1080 / 2) + height)
		{
			if (data->wall_face == NO)
				my_mlx_pixel_put(img, num_rayon, i, 0x000000FF);
			else if (data->wall_face == SO)
				my_mlx_pixel_put(img, num_rayon, i, 0x00FF0000);
			else if (data->wall_face == WE)
				my_mlx_pixel_put(img, num_rayon, i, 0x0000FF00);
			else if (data->wall_face == EA)
				my_mlx_pixel_put(img, num_rayon, i, 0x00FF00FF);
			else
				my_mlx_pixel_put(img, num_rayon, i, 0x00AAAAAA);
		}
		if (i >= (1080 / 2) + height)
			my_mlx_pixel_put(img, num_rayon, i, 0x00FFFFFF);
		i++;
	}
}
