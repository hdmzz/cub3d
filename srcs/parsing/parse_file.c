/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:03:25 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/26 20:29:43 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_file(char *name_file, t_cube *data)
{
	int fd;

	// verif extansion
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error on acces to file\n"), exit(1));
	set_ressource(fd, data);
	set_map(fd, data);
}