/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:55:56 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/26 20:57:34 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void go_to_end_of_ressource(int fd);
void	print_map(int fd);

void set_map(int fd, t_cube *data)
{
	(void) data;
	print_map(fd);
	// close(fd);
}

void	print_map(int fd)
{
	char *line;
	int height;

	height = 0;
	ft_printf("Start print map\n");
	line = get_next_line(fd);
	while (line && ft_same_str(line, ""))
	{
		// ft_printf("%s\n", line);
		line = get_next_line(fd);
	}
	while (line)
	{
		height++;
		ft_printf("%s\n", line);
		line = get_next_line(fd);
	}
	if (line)
		return (ft_printf("Error empty line in/after map\n"), exit(1));
	ft_printf("hauteur : %d\n", height);
}

// void	get_map(char *name_file)
// {
// 	int		fd;
// 	char	*line;
// 	int		num_elem;
	
// 	num_elem = 0;
// 	fd = open(name_file, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!ft_same_str(line, ""))
// 			num_elem++;
// 		// ft_printf("%d", num_elem);
// 		if (num_elem > 6)
// 			ft_printf("%s\n", line);
// 		line = get_next_line(fd);
// 	}
// }