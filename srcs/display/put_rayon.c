/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_rayon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:35:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/10 21:18:17 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sphere(t_img *img, float point[2]);

void put_rayon(t_cube *data, t_img *img)
{
	int		basic_vect[2];
	float	point[2];
	float	rad;
	float rotation;
	int nbr_rayon;

	nbr_rayon = 0;
	rotation = data->perso.orientation - 30;
	point[0] = data->perso.pix_pos[0];
	point[1] = data->perso.pix_pos[1];

	if (rotation < 0)
		rotation += 360;
	while (nbr_rayon < 1920)
	{		
		point[0] = data->perso.pix_pos[0];
		point[1] = data->perso.pix_pos[1];
		basic_vect[0] = 0;
		basic_vect[1] = 1;
		rad = rotation * (M_PI / 180);
		data->perso.front_vect[0] = basic_vect[0] * cosf(rad) + basic_vect[1] * sinf(rad);
		data->perso.front_vect[1] = basic_vect[0] * sinf(rad) - basic_vect[1] * cosf(rad);
		// printf("x : %f y : %f\n", data->perso.front_vect[0], data->perso.front_vect[1]);
		while (data->map.map[(int) point[1] / 15][(int) point[0] / 15] != '1')
		{
			point[0] += data->perso.front_vect[0];
			point[1] += data->perso.front_vect[1];
		}
		point[0] = point[0] + (110 - data->perso.pix_pos[0]);
		point[1] = point[1] + (170 - data->perso.pix_pos[1]);
		put_sphere(img, point);
		rotation += (float) 60 / 1920;
		nbr_rayon++;
		if (rotation >= 360)
			rotation -= 360;
	}
}


void	put_sphere(t_img *img, float point[2])
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