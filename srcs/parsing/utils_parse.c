/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:09:37 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/11 14:28:28 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_already_set(int ident, t_cube *data);

int	get_identifier(char *line, t_cube *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (verif_already_set(NO, data));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (verif_already_set(SO, data));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (verif_already_set(WE, data));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (verif_already_set(EA, data));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (verif_already_set(F, data));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (verif_already_set(C, data));
	else
		return (-1);
}

int	verif_already_set(int ident, t_cube *data)
{
	// if (ident == NO && data->north_img->img != NULL)
	// 	return (ft_printf("Error north image is already set\n"), exit(1), -1);
	// if (ident == SO && data->south_img->img != NULL)
	// 	return (ft_printf("Error south image is already set\n"), exit(1), -1);
	// if (ident == WE && data->west_img->img != NULL)
	// 	return (ft_printf("Error west image is already set\n"), exit(1), -1);
	// if (ident == EA && data->east_img->img != NULL)
	// 	return (ft_printf("Error east image is already set\n"), exit(1), -1);
	if (ident == F && data->floor_color[0] != -1)
		return (ft_printf("Error floor color is already set\n"), exit(1), -1);
	if (ident == C && data->ceil_color[0] != -1)
		return (ft_printf("Error ceiling color is already set\n"), exit(1), -1);
	return (ident);
}
