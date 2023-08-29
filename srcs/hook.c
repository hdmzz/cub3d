/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:24:07 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/29 17:24:58 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int press(int keycode, t_cube *data);
static int unpress(int keycode, t_cube *data);
static int loop(t_cube *data);

void	init_hook(t_cube *data)
{
	data->key_press[0] = 0;
	data->key_press[1] = 0;
	data->key_press[2] = 0;
	data->key_press[3] = 0;
	mlx_hook(data->win, ON_KEYDOWN, 1L<<0, press, data);
	mlx_hook(data->win, ON_KEYUP, 1L<<1, unpress, data);
	mlx_loop_hook(data->mlx, loop, data);
}

static int press(int keycode, t_cube *data)
{
	(void) keycode;
	(void) data;
	
	if (keycode == 65307) //esc
	{
		// mlx_do_key_autorepeaton(data->mlx);
		//faut free mon reuf;
		exit(1);
	}
	//w : 119 | a : 97 | s : 115 | d : 100
	if (keycode == 119)
		data->key_press[0] = 1;
	if (keycode == 97)
		data->key_press[1] = 1;
	if (keycode == 115)
		data->key_press[2] = 1;
	if (keycode == 100)
		data->key_press[3] = 1;
	data->keycode = keycode;
	ft_printf("press %d\n", keycode);
	return (0);
}

static int unpress(int keycode, t_cube *data)
{
	(void) keycode;
	(void) data;

	if (keycode == 119)
		data->key_press[0] = 0;
	if (keycode == 97)
		data->key_press[1] = 0;
	if (keycode == 115)
		data->key_press[2] = 0;
	if (keycode == 100)
		data->key_press[3] = 0;
	ft_printf("unpress %d\n", keycode);
	return (0);
}

static int loop(t_cube *data)
{
	if (data->key_press)
	{
		//w : 119 | a : 97 | s : 115 | d : 100
		if (data->key_press[0])
		{
			data->perso.pix_pos[1] -= 1;
			display_windows(data);
		}
		if (data->key_press[1])
		{
			data->perso.pix_pos[0] -= 1;
			display_windows(data);
		}
		if (data->key_press[2])
		{
			data->perso.pix_pos[1] += 1;
			display_windows(data);
		}
		if (data->key_press[3])
		{
			data->perso.pix_pos[0] += 1;
			display_windows(data);	
		}
	}
	return (0);
}