/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_windows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:17:09 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/27 10:45:02 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_windows(t_cube *data)
{
	t_img	img;
	t_img	test;
	int size;
	int point[2];

	size = 10;
	img.img = mlx_new_image(data->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	data->all_win = img;
	put_recasting(data, &img);
	put_minimap(data, &img);
	// put_rayon(data, &img);
	point[0] = 110 - 15;
	point[1] = 170 - 15;
	test.img = mlx_xpm_file_to_image(data->mlx, "img/perso2.xpm", &size, &size);
	put_img_to_img(data, &test, &img, point);
	if (data->mode_full_map)
		put_all_map(data, &img);
	if (data->mode_settings)
		put_settings(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_set_font(data->mlx, data->win, "*-*-*-*-*-*-*-*-*-*-*-*-100-*-16");
	if (data->mode_settings)
	{
		mlx_string_put(data->mlx, data->win, 720, 320 + 16, 0xFFFFFF, "Speed :");
		mlx_string_put(data->mlx, data->win, 720, 470 + 16, 0xFFFFFF, "FOV :");
		mlx_string_put(data->mlx, data->win, 720, 620 + 16, 0xFFFFFF, "Mouse sensibility :");
	}
	mlx_string_put(data->mlx, data->win, data->center_north[0] - 4, data->center_north[1] + 7, 0x000000, "N");
	// mlx_put_image_to_window(data->mlx, data->win, test.img, 110 - 15, 170 - 15);
	// mlx_destroy_image(data->mlx, img.img);
}
