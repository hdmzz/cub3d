/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:21 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/29 11:13:19 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// The  strspn()  function calculates the length of the initial
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

int	check_walls(char **map, int tab_len)//a enlever cest de lamerde
{
	int	y;

	y = -1;
	while (++y < tab_len)
	{
		//reste que des F 0 1 et des espaces
		if (ft_strspn(map[y], "F01 ") != ft_strlen(map[y]))
			return (error_parsing("Invalid map", NULL, 0));
	}
	return (1);
}
