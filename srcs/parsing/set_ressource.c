/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ressource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajakubcz <ajakubcz@42Lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:52:44 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/08/27 18:20:22 by ajakubcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verif_and_stock_ressource(char *line, t_cube *data);
static void	do_img_ressource(int ident, char *line, t_cube *data);
static char	*get_name_img_file(char *line);
static void	do_color_ressource(char *line, int color[3]);

void set_ressource(int fd, t_cube *data)
{
	char	*line;
	int		num_elem;
	
	num_elem = 0;
	line = get_next_line(fd);
	while (line && num_elem < 6)
	{
		// ft_printf("%s\n", line);
		if (!ft_same_str(line, ""))
		{
			verif_and_stock_ressource(line, data);
			num_elem++;
		}
		if (num_elem == 6)
			break;
		line = get_next_line(fd);
	}
	if (num_elem != 6)
		return (ft_printf("Not enough ressouces\n"), exit(1));
}

static void	verif_and_stock_ressource(char *line, t_cube *data)
{
	int ident;
	
	(void) data;
	ident = get_identifier(line);
	if (ident == -1)
		return (ft_printf("Not good identifier\n"), exit(1));
	if (ident == NO || ident == SO || ident == EA || ident == WE)
		do_img_ressource(ident, line, data);
	else if (ident == F)
		do_color_ressource(line, data->floor_color);
	else if (ident == C)
		do_color_ressource(line, data->ceil_color);
}

static void	do_img_ressource(int ident, char *line, t_cube *data)
{
	char *img_file;
	int size;

	size = 100;
	img_file = get_name_img_file(line);
	if (!img_file)
		return (ft_printf("Not good file\n"), exit(1));
	// if (!correct_file(img_file))
	// 	return (ft_printf("Not good file\n"), exit(1));
	if (ident == NO)
		data->north_img.img = mlx_xpm_file_to_image(data->mlx, img_file, &size, &size);
	if (ident == SO)
		data->south_img.img = mlx_xpm_file_to_image(data->mlx, img_file, &size, &size);
	if (ident == WE)
		data->west_img.img = mlx_xpm_file_to_image(data->mlx, img_file, &size, &size);
	if (ident == EA)
		data->east_img.img = mlx_xpm_file_to_image(data->mlx, img_file, &size, &size);
}

static char	*get_name_img_file(char *line)
{
	char	*img_file;
	int		i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	i++;
	if (ft_strlen(&line[i]) == 0)
		return (NULL);
	img_file = ft_strdup(&line[i]);
	//free(line);
	return (img_file);
}

static void	do_color_ressource(char *line, int color[3])
{
	int i;
	int ind;

	ind = 0;
	i = 2;
	while (ind < 3)
	{
		color[ind] = ft_atoi(&line[i]);
		ft_printf("color %d %d\n", ind, color[ind]);
		if (!ft_isdigit(line[i]))
			return (ft_printf("Not good format for color\n"), exit(1));
		while(ft_isdigit(line[i]))
			i++;
		if (line[i] != ',' && line[i] != '\0')
			return (ft_printf("Not good format for color\n"), exit(1));
		i++;
		ind++;
	}
	//verif if each int is between 0 and 255
}