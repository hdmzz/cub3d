/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:03:25 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/01 20:05:20 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_value(t_cube *data);
static void	verif_extansion(char *name_file);

void parse_file(char *name_file, t_cube *data)
{
	int fd;

	verif_extansion(name_file);
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error on acces to file\n"), exit(1));
	set_ressource(fd, data);
	set_map(fd, name_file, data);
	set_value(data);
}

static void	verif_extansion(char *name_file)
{
	int len;
	
	len = ft_strlen(name_file);
	if (!ft_same_str(".cub", &name_file[len - 4]))
		return (ft_printf("Error not good extansion .cub\n"), exit(1));
}

static void	set_value(t_cube *data)
{
	ft_printf("data : %d %d\n", data->perso.pos[0], data->perso.pos[1]);
	data->perso.pix_pos[0] = data->perso.pos[0] * 15 + 7;
	data->perso.pix_pos[1] = data->perso.pos[1] * 15 + 7;
}