/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:38:18 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/21 16:51:52 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_cadre(t_img *img);

void	put_settings(t_cube *data, t_img *img)
{
	(void) data;
	put_cadre(img);
}

void	put_cadre(t_img *img)
{
	int x;
	int y;

	x = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			if (y > 300 && y < 710 && ((x > 700 && x < 710) || (x > 1300 && x < 1310)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (x > 700 && x < 1310 && ((y > 300 && y < 310) || (y > 700 && y < 710)))
				my_mlx_pixel_put(img, x, y, 0x00000000);
			else if (y > 310 && y < 700 && x > 710 && x < 1300)
				my_mlx_pixel_put(img, x, y, 0x00AAAAAA);
			else
				my_mlx_pixel_put(img, x, y, ft_opacity(my_mlx_pixel_get(img, x, y), 0.5));
			y++;
		}
		x++;
	}
}

// void	put_cursor(t_cube *data, t_img *img, char *type)
// {
	
// }
