/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:29:41 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/28 16:08:20 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//usage err = part where the error is or what cause the error, detail = detail of the error
int		error_parsing(char *err, char *detail, int ret)
{
	ft_putstr_fd("Error\n", 2);
	if (err)
	{
		ft_putstr_fd(err, 2);
	}
	if (detail)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(detail, 2);
	}
	ft_putstr_fd("\n", 2);
	return (ret);
}
