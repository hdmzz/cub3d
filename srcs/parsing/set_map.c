/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:55:56 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/31 13:17:28 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_size(int fd, t_map *map);
void	store_map(char *name_file, t_map *map);
char	*go_to_first_line(int fd);
char	*fill_line(char *line, t_map *map);

void	print_map(char **map) //TO_DELETE
{
	int	i;

	i = 0;
	ft_printf("------------------PRINT MAP------------------\n");
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	set_map(int fd, char *name_file, t_cube *data)
{
	ft_printf("hauteur : %d largeur : %d\n", 0, 0);
	get_map_size(fd, &data->map);
	ft_printf("hauteur : %d largeur : %d\n", data->map.height, data->map.width);
	close(fd);
	store_map(name_file, &data->map);
	print_map(data->map.map);
	verif_map(data);
}

void	get_map_size(int fd, t_map *map)
{
	char	*line;

	puts("test");
	map->height = 0;
	map->width = 0;
	puts("test");
	line = get_next_line(fd);
	while (line && ft_same_str(line, ""))
	{
		line = get_next_line(fd);
	}
	while (line && !ft_same_str(line, ""))
	{
		if ((int) ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		map->height++;
		// ft_printf("%s\n", line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!ft_same_str(line, ""))
			return (ft_printf("Error there is something after map\n"), exit(1));
		line = get_next_line(fd);
	}
}

void	store_map(char *name_file, t_map *map)
{
	int		fd;
	char	*line;
	int		num_line;

	num_line = 0;
	fd = open(name_file, O_RDONLY);
	//verif fd
	map->map = malloc(sizeof(char *) * (map->height + 1));
	line = go_to_first_line(fd);
	printf("first map line : %s\n", line);
	while (line && !ft_same_str(line, ""))
	{
		map->map[num_line] = fill_line(line, map);
		//if (!map->map[num_line])
		// 	free;
		line = get_next_line(fd);
		num_line++;
	}
	map->map[num_line] = NULL;
	//verif si num_line correspond à map->height
}

char	*go_to_first_line(int fd)
{
	char	*line;
	int		num_elem;

	num_elem = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_same_str(line, ""))
			num_elem++;
		// ft_printf("%d", num_elem);
		if (num_elem > 6)
			return (line);
		line = get_next_line(fd);
	}
	return (NULL);
}

char	*fill_line(char *line, t_map *map)
{
	char	*to_return;
	int		i;

	to_return = ft_strdup(line);
	i = ft_strlen(line);
	while (i < map->width)
	{
		to_return = ft_strjoin(to_return, " ");
		i++;
	}
	return (to_return);
}
