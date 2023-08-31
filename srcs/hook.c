/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:24:07 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/31 13:03:10 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	press(int keycode, t_cube *data);
static int	unpress(int keycode, t_cube *data);
static int	loop(t_cube *data);

void	init_hook(t_cube *data)
{
	data->key_press[0] = 0;
	data->key_press[1] = 0;
	data->key_press[2] = 0;
	data->key_press[3] = 0;
	data->key_press[4] = 0;
	data->key_press[5] = 0;
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, press, data);
	mlx_hook(data->win, ON_KEYUP, 1L << 1, unpress, data);
	mlx_loop_hook(data->mlx, loop, data);
}

//w : 119 | a : 97 | s : 115 | d : 100 | left : 65361 | right : 65363
static int	press(int keycode, t_cube *data)
{
	if (keycode == 65307)
	{
		//faut free mon reuf;
		exit(1);
	}
	// ft_printf("press %d\n", keycode);
	if (keycode == 119)
		data->key_press[0] = 1;
	if (keycode == 97)
		data->key_press[1] = 1;
	if (keycode == 115)
		data->key_press[2] = 1;
	if (keycode == 100)
		data->key_press[3] = 1;
	if (keycode == 65361)
		data->key_press[4] = 1;
	if (keycode == 65363)
		data->key_press[5] = 1;
	return (0);
}

static int	unpress(int keycode, t_cube *data)
{
	// ft_printf("unpress %d\n", keycode);
	if (keycode == 119)
		data->key_press[0] = 0;
	if (keycode == 97)
		data->key_press[1] = 0;
	if (keycode == 115)
		data->key_press[2] = 0;
	if (keycode == 100)
		data->key_press[3] = 0;
	if (keycode == 65361)
		data->key_press[4] = 0;
	if (keycode == 65363)
		data->key_press[5] = 0;
	return (0);
}

void	add_vect_dir(t_cube *data, int orientation)
{
	float	vect_to_add[2];
	int		basic_vect[2];
	float	rad;

	basic_vect[0] = 0;
	basic_vect[1] = 1;
	if (orientation >= 360)
		orientation -= 360;
	rad = orientation * (M_PI / 180);
	vect_to_add[0] = basic_vect[0] * cosf(rad) - basic_vect[1] * sinf(rad);
	vect_to_add[1] = basic_vect[0] * sinf(rad) + basic_vect[1] * cosf(rad);
	data->perso.vect_dir[0] += vect_to_add[0];
	data->perso.vect_dir[1] += vect_to_add[1];
}

void	change_vect_dir(t_cube *data, int *key_press)
{
	data->perso.vect_dir[0] = 0;
	data->perso.vect_dir[1] = 0;
	if (key_press[0])
		add_vect_dir(data, data->perso.orientation + 180);
	if (key_press[1])
		add_vect_dir(data, data->perso.orientation + 90);
	if (key_press[2])
		add_vect_dir(data, data->perso.orientation);
	if (key_press[3])
		add_vect_dir(data, data->perso.orientation + 270);
}

int	is_keypress(int key_press[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (key_press[i])
			return (1);
		i++;
	}
	return (0);
}

static int	loop(t_cube *data)
{
	//w : 119 | a : 97 | s : 115 | d : 100
	if (data->key_press[0] || data->key_press[1] || data->key_press[2] || data->key_press[3])
	{
		change_vect_dir(data, data->key_press);
		data->perso.pix_pos[0] += data->perso.vect_dir[0];
		data->perso.pix_pos[1] += data->perso.vect_dir[1];
	}
	if (data->key_press[4])
	{
		data->perso.orientation -= 1;
		if (data->perso.orientation <= 360)
			data->perso.orientation += 360;
	}
	if (data->key_press[5])
	{
		data->perso.orientation += 1;
		if (data->perso.orientation >= 360)
			data->perso.orientation -= 360;
	}
	if (is_keypress(data->key_press))
		display_windows(data);
	return (0);
}
