/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_windows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:17:09 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/29 10:29:29 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_windows(t_cube *data)
{
	t_img	img;
	
	img.img = mlx_new_image(data->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//put_all_map(data, &img);
	put_minimap(data, &img);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}