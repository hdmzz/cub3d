/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:21 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/28 12:38:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// The  strspn()  function calculates the length (in bytes) of the initial
//segment of s which consists entirely of bytes in accept.
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
}

int	check_walls(char **map, int tab_len)//tab len = map->height
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (ft_strspn(map[0], "1") != ft_strlen(map[0]))//premiere ligne
		return (0);
	if (ft_strspn(map[tab_len], "1") != ft_strlen(map[tab_len]))//derniere ligne
		return (0);
	while (y < tab_len)
	{
		//est ce que les NSEW on ete gerer ici
		
	}
}
