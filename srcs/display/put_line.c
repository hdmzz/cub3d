/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:15:52 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/11 23:15:37 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		get_color(int color[3])
{
	int to_return;

	to_return = 0;
	to_return += color[0] << 16;
	to_return += color[1] << 8;
	to_return += color[2];
	return (to_return);
}

float ft_modf(float nbr, int div)
{
    while (nbr > (float) div)
        nbr -= div;
    return (nbr);
}

void    put_north_texture(t_img *img, int x, int y, t_cube *data, double height)
{
    int pos_pix_texture[2];
    int color;

    (void) height;
    pos_pix_texture[0] = ft_modf(data->coli_point[0], 15) * 100 / 15;
    pos_pix_texture[1] = ((y - ((1080 / 2) - height)) * 50) / height;
    if (pos_pix_texture[1] >= 100)
        pos_pix_texture[1] = 50;
    color = my_mlx_pixel_get(&data->north_img, pos_pix_texture[0], pos_pix_texture[1]);
    my_mlx_pixel_put(img, x, y, color);
}

void    put_south_texture(t_img *img, int x, int y, t_cube *data, double height)
{
    int pos_pix_texture[2];
    int color;

    (void) height;
    pos_pix_texture[0] = ft_modf(data->coli_point[0], 15) * 100 / 15;
    pos_pix_texture[0] = 100 - pos_pix_texture[0];
    pos_pix_texture[1] = ((y - ((1080 / 2) - height)) * 50) / height;
    // if (pos_pix_texture[1] >= 100)
    //     pos_pix_texture[1] = 50;
    color = my_mlx_pixel_get(&data->south_img, pos_pix_texture[0], pos_pix_texture[1]);
    my_mlx_pixel_put(img, x, y, color);
}

void    put_west_texture(t_img *img, int x, int y, t_cube *data, double height)
{
    int pos_pix_texture[2];
    int color;

    (void) height;
    pos_pix_texture[0] = ft_modf(data->coli_point[1], 15) * 100 / 15;
    pos_pix_texture[1] = ((y - ((1080 / 2) - height)) * 50) / height;
    if (pos_pix_texture[1] >= 100)
        pos_pix_texture[1] = 50;
    color = my_mlx_pixel_get(&data->west_img, pos_pix_texture[0], pos_pix_texture[1]);
    my_mlx_pixel_put(img, x, y, color);
}

void    put_east_texture(t_img *img, int x, int y, t_cube *data, double height)
{
    int pos_pix_texture[2];
    int color;

    (void) height;
    pos_pix_texture[0] = ft_modf(data->coli_point[1], 15) * 100 / 15;
    pos_pix_texture[1] = ((y - ((1080 / 2) - height)) * 50) / height;
    if (pos_pix_texture[1] >= 100)
        pos_pix_texture[1] = 50;
    color = my_mlx_pixel_get(&data->east_img, pos_pix_texture[0], pos_pix_texture[1]);
    my_mlx_pixel_put(img, x, y, color);
}


void	put_line(int num_rayon, double dist ,t_cube *data, t_img *img)
{
	int i;

	i = 0;
	// printf("dist : %f\n", dist);
	double height = (double) (1 / dist) * 10000;
    data->north_img.addr = mlx_get_data_addr(data->north_img.img, &data->north_img.bits_per_pixel, \
		&data->north_img.line_length, &data->north_img.endian);
    data->south_img.addr = mlx_get_data_addr(data->south_img.img, &data->south_img.bits_per_pixel, \
		&data->south_img.line_length, &data->south_img.endian);
    data->west_img.addr = mlx_get_data_addr(data->west_img.img, &data->west_img.bits_per_pixel, \
		&data->west_img.line_length, &data->west_img.endian);
    data->east_img.addr = mlx_get_data_addr(data->east_img.img, &data->east_img.bits_per_pixel, \
		&data->east_img.line_length, &data->east_img.endian);
	while (i < 1080)
	{
		if (i > (1080 / 2) - height && i < (1080 / 2) + height)
		{
			if (data->wall_face == NO)
				put_north_texture(img, num_rayon, i, data, height);
			else if (data->wall_face == SO)
				put_south_texture(img, num_rayon, i, data, height);
			else if (data->wall_face == WE)
				put_west_texture(img, num_rayon, i, data, height);
			else if (data->wall_face == EA)
				put_east_texture(img, num_rayon, i, data, height);
			else
				my_mlx_pixel_put(img, num_rayon, i, 0x00AAAAAA);
		}
		if (i >= (1080 / 2) + height)
			my_mlx_pixel_put(img, num_rayon, i, get_color(data->floor_color));
		if (i <= (1080 / 2) - height)
			my_mlx_pixel_put(img, num_rayon, i, get_color(data->ceil_color));
		i++;
	}
}

// void	put_line(int num_rayon, double dist ,t_cube *data, t_img *img)
// {
// 	int i;

// 	i = 0;
// 	(void) num_rayon;
// 	(void) data;
// 	(void) img;
// 	// printf("dist : %f\n", dist);
// 	double height = (double) (1 / dist) * 10000;
// 	while (i < 1080)
// 	{
// 		if (i > (1080 / 2) - height && i < (1080 / 2) + height)
// 		{
// 			if (data->wall_face == NO)
// 				my_mlx_pixel_put(img, num_rayon, i, 0x000000FF);
// 			else if (data->wall_face == SO)
// 				my_mlx_pixel_put(img, num_rayon, i, 0x00FF0000);
// 			else if (data->wall_face == WE)
// 				my_mlx_pixel_put(img, num_rayon, i, 0x0000FF00);
// 			else if (data->wall_face == EA)
// 				my_mlx_pixel_put(img, num_rayon, i, 0x00FF00FF);
// 			else
// 				my_mlx_pixel_put(img, num_rayon, i, 0x00AAAAAA);
// 		}
// 		if (i >= (1080 / 2) + height)
// 			my_mlx_pixel_put(img, num_rayon, i, get_color(data->floor_color));
// 		if (i <= (1080 / 2) - height)
// 			my_mlx_pixel_put(img, num_rayon, i, get_color(data->ceil_color));
// 		i++;
// 	}
// }