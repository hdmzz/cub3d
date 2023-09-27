/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_recasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:43:41 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/27 10:07:27 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_dist(int num_rayon, float rotation, t_cube *data, t_img *img);
void get_precise_dist(t_cube *data, float point[2]);
double get_angle(int num_rayon, float rotation, t_cube *data);
int good_char(char c);
int col_rayon(t_cube *data, float point[2], float preci);

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
	rotation = data->perso.orientation - (data->value_param[FOV] / 2);
	if (rotation < 0)
		rotation += 360;
	printf("rotation start : %f\n", rotation);
	while (num_rayon < 1920)
	{
		put_line(num_rayon, get_dist(num_rayon, rotation, data, img), data, img);
		rotation += (float) data->value_param[FOV] / 1920;
		num_rayon++;
		if (rotation >= 360)
			rotation -= 360;
	}
	printf("rotation end : %f\n", rotation);

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
	// else
	// 	data->wall_face = -1;
}

double get_dist(int num_rayon, float rotation, t_cube *data, t_img *img)
{
	int		basic_vect[2];
	// float	point[2];
	double	rad;
	long double	hyp;
	
	(void) img;
	data->coli_point[0] = data->perso.pix_pos[0];
	data->coli_point[1] = data->perso.pix_pos[1];
	basic_vect[0] = 0;
	basic_vect[1] = 1;
	rad = rotation * (M_PI / 180);
	data->perso.front_vect[0] = basic_vect[0] * cosf(rad) + basic_vect[1] * sinf(rad);
	data->perso.front_vect[1] = basic_vect[0] * sinf(rad) - basic_vect[1] * cosf(rad);
	// printf("x : %f y : %f\n", data->perso.front_vect[0], data->perso.front_vect[1]);
	get_precise_dist(data, data->coli_point);
	set_wall_face(data, data->coli_point);
	// put_sphere2(img, data->coli_point);
	// printf("%Lf %Lf %f\n", data->coli_point[0], data->coli_point[1], pow((data->perso.pix_pos[0] - data->coli_point[0]), 2) + pow((data->perso.pix_pos[1] - data->coli_point[1]), 2));
	hyp = sqrtl(pow((data->perso.pix_pos[0] - data->coli_point[0]), 2) + pow((data->perso.pix_pos[1] - data->coli_point[1]), 2));
	rad = get_angle(num_rayon, rotation, data) * (M_PI / 180);
	// printf("hyp : %Lf\n", hyp);
	// printf("value : %f\n", (float) ((float) data->value_param[FOV] / 60));
	return ((double) hyp * cosf(rad) * ((float) ((float) data->value_param[FOV] / (float) 60)));
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
	while (!col_rayon(data, point, 0.1))
	{
		point[0] += data->perso.front_vect[0] / 0.1;
		point[1] += data->perso.front_vect[1] / 0.1;
	}
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
	// point[0] += data->perso.front_vect[0] / 100;
	// point[1] += data->perso.front_vect[1] / 100;
	// while (!col_rayon(data, point, 500))
	// {
	// 	point[0] += data->perso.front_vect[0] / 500;
	// 	point[1] += data->perso.front_vect[1] / 500;
	// }
}

// void get_precise_dist(t_cube *data, float point[2])
// {
// 	float coli_point[2];
	
// 	while (!col_rayon(data, point, 1))
// 	{
// 		point[0] += data->perso.front_vect[0];
// 		point[1] += data->perso.front_vect[1];
// 	}
// 	while (!col_rayon(data, point, 10))
// 	{
// 		point[0] += data->perso.front_vect[0] / 10;
// 		point[1] += data->perso.front_vect[1] / 10;
// 	}
// 	if (point[0] / 15 != (point[0] + data->perso.front_vect[0]) / 15)
// 	{
// 		if ((point[0] + data->perso.front_vect[0]) / 15 < point[0] / 15)
// 		{
// 			coli_point[0] = ((int) point[0] / 15) * 15;
// 			coli_point[1] = point[1] + (coli_point[0] - point[0]) / (data->perso.front_vect[0] - point[0]) * (data->perso.front_vect[1] - point[1]);
// 			if (good_char(data->map.map[(int) coli_point[1] / 15][(int) coli_point[0] / 15]) && !good_char(data->map.map[(int) coli_point[1] / 15][(int) (coli_point[0] - 0.01) / 15]))
// 			{
// 				point[0] = coli_point[0];
// 				point[1] = coli_point[1];
// 				data->wall_face = WE;
// 				return ;
// 			}
// 		}
// 		if ((point[0] + data->perso.front_vect[0]) / 15 > point[0] / 15)
// 		{
// 			coli_point[0] = ((int) (point[0] + data->perso.front_vect[0]) / 15) * 15;
// 			coli_point[1] = point[1] + (coli_point[0] - point[0]) / (data->perso.front_vect[0] - point[0]) * (data->perso.front_vect[1] - point[1]);
// 			if (!good_char(data->map.map[(int) coli_point[1] / 15][(int) coli_point[0] / 15]) && good_char(data->map.map[(int) coli_point[1] / 15][(int) (coli_point[0] - 0.01) / 15]))
// 			{
// 				point[0] = coli_point[0];
// 				point[1] = coli_point[1];
// 				data->wall_face = EA;
// 				return ;
// 			}
// 		}
// 	}
// 	if (point[1] / 15 != (point[1] + data->perso.front_vect[1]) / 15)
// 	{
// 		if ((point[1] + data->perso.front_vect[1]) / 15 < point[1] / 15)
// 		{
// 			coli_point[1] = ((int) point[1] / 15) * 15;
// 			coli_point[0] = point[0] + (coli_point[1] - point[1]) / (data->perso.front_vect[1] - point[1]) * (data->perso.front_vect[0] - point[0]);
// 			printf("%f %f\n", coli_point[0], coli_point[1]);
// 			if (good_char(data->map.map[(int) coli_point[1] / 15][(int) coli_point[0] / 15]) && !good_char(data->map.map[(int) (coli_point[1] - 0.01) / 15][(int) coli_point[0] / 15]))
// 			{
// 				point[0] = coli_point[0];
// 				point[1] = coli_point[1];
// 				data->wall_face = NO;
// 				return ;
// 			}
// 		}
// 		if ((point[1] + data->perso.front_vect[1]) / 15 > point[1] / 15)
// 		{
// 			coli_point[1] = ((int) (point[1] + data->perso.front_vect[1]) / 15) * 15;
// 			coli_point[0] = point[0] + (coli_point[1] - point[1]) / (data->perso.front_vect[1] - point[1]) * (data->perso.front_vect[0] - point[0]);
// 			if (!good_char(data->map.map[(int) coli_point[1] / 15][(int) coli_point[0] / 15]) && good_char(data->map.map[(int) (coli_point[1] - 0.01) / 15][(int) coli_point[0] / 15]))
// 			{
// 				point[0] = coli_point[0];
// 				point[1] = coli_point[1];
// 				data->wall_face = SO;
// 				return ;
// 			}
// 		}
// 	}
// 	data->wall_face = -1;
// }

int col_rayon(t_cube *data, float point[2], float preci)
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

