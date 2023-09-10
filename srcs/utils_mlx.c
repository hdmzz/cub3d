/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:08:52 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/10 23:07:49 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_img_to_img(t_cube *data, t_img *img, t_img *to_img, int point[2])
{
	int	i;
	int	j;
	int	color;

	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	i = 0;
	while (i < 30)
	{
		j = 0;
		while (j < 30)
		{
			color = my_mlx_pixel_get(img, i, j);
			if (color > 0)
				my_mlx_pixel_put(to_img, i + point[0], j + point[1], \
					mlx_get_color_value(data->mlx, color));
			j++;
		}
		i++;
	}
}
