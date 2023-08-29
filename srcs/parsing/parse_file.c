/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:03:25 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/29 17:26:44 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_value(t_cube *data)
{
	ft_printf("data : %d %d\n", data->perso.pos[0], data->perso.pos[1]);
	data->perso.pix_pos[0] = data->perso.pos[0] * 15 + 7;
	data->perso.pix_pos[1] = data->perso.pos[1] * 15 + 7;
}

void parse_file(char *name_file, t_cube *data)
{
	int fd;

	// verif extansion
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error on acces to file\n"), exit(1));
	set_ressource(fd, data);
	set_map(fd, name_file, data);
	set_value(data);
}