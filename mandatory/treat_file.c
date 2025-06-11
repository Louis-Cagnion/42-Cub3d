/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:47:09 by locagnio          #+#    #+#             */
/*   Updated: 2025/05/08 18:37:27 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_elem_infos(char *elems[])
{
	elems[0] = "NO";
	elems[1] = "SO";
	elems[2] = "WE";
	elems[3] = "EA";
	elems[4] = "F";
	elems[5] = "C";
}

static int	get_rgb(t_map *map, char *info, int elem)
{
	int	rgb[3];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		rgb[j++] = ft_natoi(info, &i);
		if (!ft_isnum(info[i - 1]) || rgb[j - 1] > 255 || rgb[j - 1] < 0)
			return (ft_error("Invalid RGB color.\n"), 0);
		if (i != '\n')
			i++;
	}
	while (info[i] && info[i] != '\n')
		if (ft_isnum(info[i++]))
			return (ft_error("Too many RGB colors.\n"), 0);
	if (elem == 4)
		map->f_rgb = (rgb[0] * 256 * 256) + (rgb[1] * 256) + rgb[2];
	else if (elem == 5)
		map->c_rgb = (rgb[0] * 256 * 256) + (rgb[1] * 256) + rgb[2];
	return (1);
}

/* get the valid elements in the structure */
static int	get_map_infos(t_map *map, char *info, char **elem, int elem_nb)
{
	int	len_line;

	if (elem_nb < 4)
	{
		len_line = ft_strclen(info, '\n');
		if (len_line < 4)
			return (ft_error("No informations for an elem.\n"), 0);
		len_line -= 3;
		*elem = ft_strndup(info + 3, len_line);
		if (!path_is_valid(*elem))
			return (0);
	}
	else if ((elem_nb < 6) && !get_rgb(map, info + 2, elem_nb))
		return (0);
	return (1);
}

/* check if the elements are valid and get them */
static int	check_elems(char *file_infos, int *i, char *elems[], t_map *map)
{
	int	j;
	int	count;

	j = 0;
	count = 6;
	while (file_infos[*i] && count)
	{
		while (ft_strchr("\n\r", file_infos[*i]))
			(*i)++;
		if (file_infos[*i]
			&& !ft_strncmp(file_infos + *i, elems[j], ft_strlen(elems[j])))
		{
			if (!get_map_infos(map, file_infos + *i, get_elem(map, j), j))
				return (0);
			j++;
		}
		else
			return (ft_error("Elements aren't in right order.\n"), 0);
		count--;
		while (file_infos[*i] && file_infos[*i] != '\n')
			(*i)++;
	}
	if (!count)
		return (1);
	return (ft_error("Lacking elements for map.\n"), 0);
}

int	treat_file(char *map_name, t_game *game)
{
	char	*file_infos;
	char	*elems[6];
	int		i;

	i = 0;
	init_elem_infos(elems);
	file_infos = ft_read_file(map_name);
	if (!file_infos || !file_infos[0])
		return (ft_error("Empty file.\n"), 1);
	if (!check_elems(file_infos, &i, elems, &game->map))
		return (free(file_infos), 1);
	while (file_infos[i] && file_infos[i] != '\n')
		i++;
	while (file_infos[i] && !ft_strchr("01NSEW ", file_infos[i]))
		i++;
	if (!file_infos[i])
	{
		free(file_infos);
		return (ft_error("No map given.\n"), 1);
	}
	if (treat_map(file_infos + i, -1, game))
		return (1);
	free(file_infos);
	return (!game->map.map || !game->map.map_array);
}
