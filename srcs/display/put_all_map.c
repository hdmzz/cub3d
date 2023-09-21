/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_all_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:38:18 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/21 16:09:15 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_all_map2(t_img *img, t_cube *data);
void	put_perso2(t_img *img, t_cube *data);

void	put_all_map(t_cube *data, t_img *img)
{
	ft_printf("start put all map\n");
	put_all_map2(img, data);
	ft_printf("end put all map\n");
	put_perso2(img, data);
}

void	put_all_map2(t_img *img, t_cube *data)
{
	int x;
	int y;

	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			if (x < data->map.width * 15 && y < data->map.height * 15 && data->map.map[y / 15][x / 15] == '1')
				my_mlx_pixel_put(img, x, y, 0x00666666);
			else if (x < data->map.width * 15 && y < data->map.height * 15 && data->map.map[y / 15][x / 15] != ' ')
				my_mlx_pixel_put(img, x, y, 0x00DDDDDD);
			else 
				my_mlx_pixel_put(img, x, y, ft_opacity(my_mlx_pixel_get(img, x, y), 0.5));
			y++;
		}
		x++;
	}
}

void	put_perso2(t_img *img, t_cube *data)
{
	int		x;
	int		y;
	float	dist;

	x = data->perso.pix_pos[0] - 10;
	while (x < data->perso.pix_pos[0] + 10)
	{
		y = data->perso.pix_pos[1] - 10;
		while (y < data->perso.pix_pos[1] + 10)
		{
			dist = sqrt(pow((x - (data->perso.pix_pos[0])), 2) + pow((y - (data->perso.pix_pos[1])), 2));
			if (dist < 5)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}
