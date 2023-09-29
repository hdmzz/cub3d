/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ressource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:52:44 by ajakubcz          #+#    #+#             */
/*   Updated: 2023/09/28 16:14:31 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verif_and_stock_ressource(char *line, t_cube *data);
static void	do_img_ressource(int ident, char *line, t_cube *data);
static char	*get_name_img_file(char *line);
static void	do_color_ressource(char *line, int color[3]);

void	set_ressource(int fd, t_cube *data)
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
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (num_elem != 6)
		return (ft_printf("Not enough ressouces\n"), exit(1));
}

static void	verif_and_stock_ressource(char *line, t_cube *data)
{
	int	ident;

	(void) data;
	ident = get_identifier(line, data);
	if (ident == -1)
		return (free(line), ft_printf("Not good identifier\n"), exit(1));
	if (ident == NO || ident == SO || ident == EA || ident == WE)
		do_img_ressource(ident, line, data);
	else if (ident == F)
		do_color_ressource(line, data->floor_color);
	else if (ident == C)
		do_color_ressource(line, data->ceil_color);
}

// static void	do_img_ressource(int ident, char *line, t_cube *data)
// {
// 	char	*file;
// 	int		s;

// 	s = 30;
// 	file = get_name_img_file(line);
// 	ft_printf("file : %s|\n", file);
// 	if (!file) // || !correct_file(file)
// 		return (ft_printf("Error not good file\n"), exit(1));
// 	if (ident == NO)
// 		data->north_img.img = mlx_xpm_file_to_image(data->mlx, file, &s, &s);
// 	if (ident == SO)
// 		data->north_img.img = mlx_xpm_file_to_image(data->mlx, file, &s, &s);
// 	if (ident == WE)
// 		data->north_img.img = mlx_xpm_file_to_image(data->mlx, file, &s, &s);
// 	if (ident == EA)
// 		data->east_img.img = mlx_xpm_file_to_image(data->mlx, "img", &s, &s);
// 	puts("b");
// }

static void	do_img_ressource(int ident, char *line, t_cube *data)
{
	char	*file;

	file = get_name_img_file(line);
	// ft_printf("file : %s|\n", file);
	if (!file) // || !correct_file(file)
		return (ft_printf("Error not good file\n"), exit(1));
	if (ident == NO)
		f_to_img(&data->north_img, data->mlx, file, 100);
	if (ident == SO)
		f_to_img(&data->south_img, data->mlx, file, 100);
	if (ident == WE)
		f_to_img(&data->west_img, data->mlx, file, 100);
	if (ident == EA)
		f_to_img(&data->east_img, data->mlx, file, 100);
	puts("b");
}

static char	*get_name_img_file(char *line)
{
	char	*img_file;
	int		i;

	i = 0;
	while (ft_isalpha(line[i])) //skip the identifier
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(&line[i]) == 0)
		return (NULL);
	img_file = &line[i];
	return (img_file);
}

static void	do_color_ressource(char *line, int color[3])
{
	int	i;
	int	ind;

	ind = 0;
	i = 2;
	while (ind < 3)
	{
		color[ind] = ft_atoi(&line[i]);
		if (color[ind] < 0 || color[ind] > 255)
			return (ft_printf("Not good format for color\n"), free(line), exit(1));
		ft_printf("color %d %d\n", ind, color[ind]);
		if (!ft_isdigit(line[i]))
			return (ft_printf("Not good format for color\n"), free(line), exit(1));
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] != ',' && line[i] != '\0')
			return (ft_printf("Not good format for color\n"), free(line), exit(1));
		i++;
		ind++;
	}
}
