/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:00:04 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/28 13:48:32 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pos_perso(t_map *map, t_perso *perso);
void	set_perso(t_perso *perso, char orientation, int x, int y);
void	verif_if_close(t_map *map, t_perso *perso);
char	**copy(t_map *map);
int		can_fill(char c);
void	fill_map(char **cp_map, int x, int y, t_map *map);
int		verif_around(char **cp_map, int y, int x, t_map *map);

void	verif_map(t_cube *data)
{
	get_pos_perso(&data->map, &data->perso);//encore NSEW
	verif_if_close(&data->map, &data->perso);
}

void	get_pos_perso(t_map *map, t_perso *perso)
{
	int	x;
	int	y;
	int	count;

	x = -1;
	count = 0;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || \
				map->map[y][x] == 'E' || map->map[y][x] == 'W')
				{
					set_perso(perso, map->map[y][x], x, y);
					count++;
				}
		}
	}
	if (count > 1)
		return (error_parsing("Too many player positions"), exit (1));//le exit
		//faudra revoir free tout ce qu il ya a free
	ft_printf("Error no perso on map\n");
	exit(1);
}

void	set_perso(t_perso *perso, char orientation, int x, int y)
{
	perso->pos[0] = x;
	perso->pos[1] = y;
	if (orientation == 'N')
		perso->orientation = 0;
	if (orientation == 'S')
		perso->orientation = 180;
	if (orientation == 'E')
		perso->orientation = 90;
	if (orientation == 'W')
		perso->orientation = 270;
}

void	verif_if_close(t_map *map, t_perso *perso)
{
	char	**cp_map;
	int		x;
	int		y;

	x = 0;
	cp_map = copy(map);
	fill_map(cp_map, perso->pos[0], perso->pos[1], map);
	print_map(cp_map);
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (cp_map[y][x] == 'F' && !verif_around(cp_map, y, x, map))
				return (ft_printf("Error map not close\n"), exit(1));
			y++;
		}
		x++;
	}
	// free_all(cp_map);
}

int	verif_around(char **cp_map, int y, int x, t_map *map)
{
	if (x == 0 || y == 0 || x == map->width -1 || y == map->height - 1)
		return (0);
	if (cp_map[y][x + 1] == ' ' || cp_map[y][x - 1] == ' ')
		return (0);
	if (cp_map[y + 1][x] == ' ' || cp_map[y - 1][x] == ' ')
		return (0);
	return (1);
}

char	**copy(t_map *map)
{
	int		y;
	int		x;
	char	**cp_map;

	cp_map = malloc(sizeof(char *) * (map->height + 1));
	if (cp_map == NULL)
		return (ft_printf("Error allocation\n"),/* free_all(map->map),*/ NULL);
	y = 0;
	while (y < map->height)
	{
		cp_map[y] = malloc(sizeof(char) * (map->width + 1));
		if (cp_map[y] == NULL)
			return (ft_printf("Error allocation\n"),/*free_all(cp_map), free_all(map->map),*/ NULL);
		x = 0;
		while (x < map->width)
		{
			cp_map[y][x] = map->map[y][x];
			x++;
		}
		cp_map[y][x] = '\0';
		y++;
	}
	cp_map[y] = NULL;
	return (cp_map);
}

void	fill_map(char **cp_map, int x, int y, t_map *map)
{
	if (!cp_map)
		exit (1);
	cp_map[y][x] = 'F';
	if (y + 1 < map->height && can_fill(cp_map[y + 1][x]))
		fill_map(cp_map, x, y + 1, map);
	if (y - 1 >= 0 && can_fill(cp_map[y - 1][x]))
		fill_map(cp_map, x, y - 1, map);
	if (x + 1 < map->width && can_fill(cp_map[y][x + 1]))
		fill_map(cp_map, x + 1, y, map);
	if (x - 1 >= 0 && can_fill(cp_map[y][x - 1]))
		fill_map(cp_map, x - 1, y, map);
}

int	can_fill(char c)
{
	if (c != '1' && c != 'F' && c != ' ')
		return (1);
	return (0);
}
