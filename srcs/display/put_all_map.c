/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_all_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:38:18 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/27 22:20:31 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_all_map2(t_img *img, t_cube *data);
void    put_perso2(t_img *img, t_cube *data);

void put_all_map(t_cube *data)
{
    t_img	img;
	
	img.img = mlx_new_image(data->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_printf("start put all map\n");
    put_all_map2(&img, data);
    ft_printf("end put all map\n");
    put_perso2(&img, data);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}

void    put_all_map2(t_img *img, t_cube *data)
{
    int x;
    int y;

    x = 0;
    while (x < data->map.width * 20 && x < 1900)
    {
        y = 0;
        while (y < data->map.height * 20 && y < 1000)
        {
            // ft_printf("coords %d %d\n", x/20, y/20);
            if (data->map.map[y / 20][x / 20] == '1')
                my_mlx_pixel_put(img, x, y, 0x00666666);
            else if (data->map.map[y / 20][x / 20] == ' ')
                my_mlx_pixel_put(img, x, y, 0x00222222);
            else
                my_mlx_pixel_put(img, x, y, 0x00DDDDDD);
            y++;
        }
        x++;
    }
}

void    put_perso2(t_img *img, t_cube *data)
{
    int		x;
	int		y;
	float	dist;
	
	x = data->perso.pos[0] * 20 + 10 - 10;
	while (x < data->perso.pos[0] * 20 + 10 + 10)
	{
		y = data->perso.pos[1] * 20 + 10 - 10;
		while (y < data->perso.pos[1] * 20 + 10 + 10)
		{
			dist = sqrt(pow((x - (data->perso.pos[0] * 20 + 10)), 2) + pow((y - (data->perso.pos[1] * 20 + 10)), 2));
			if (dist < 5)
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}