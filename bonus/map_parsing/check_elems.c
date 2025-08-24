/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:54:50 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/17 11:29:12 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_rgb(t_tile *tile, char *info, int elem)
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
		if (info[i] != '\n')
			i++;
	}
	while (info[i] && info[i] != '\n')
		if (ft_isnum(info[i++]))
			return (ft_error("Too many RGB colors.\n"), 0);
	if (elem == 4)
		tile->f_rgb = (rgb[0] * 256 * 256) + (rgb[1] * 256) + rgb[2];
	else if (elem == 5)
		tile->c_rgb = (rgb[0] * 256 * 256) + (rgb[1] * 256) + rgb[2];
	return (1);
}

static int	get_wall_depth(char *info, char **elem, int float_len)
{
	if (*info == '1' && info++)
	{
		while (*info && *info != '\n')
			if (!ft_strchr(" \t", *(++info)))
				return (ft_error("Invalid wall depth\n"), 0);
		*elem = ft_strndup("1", 1);
		return (1);
	}
	if (*info != '0')
		return (ft_error("Invalid wall identifier\n"), 0);
	if (info[1] != '.' && info++)
	{
		while (*info && *info != '\n')
			if (!ft_strchr(" \t", *(++info)))
				return (ft_error("Invalid wall depth\n"), 0);
		return (1);
	}
	info += 2;
	while (ft_isnum(info[float_len]))
		float_len++;
	while (info[float_len] && (info[float_len] != '\n'))
		if (!ft_strchr(" \t", info[float_len]))
			return (ft_error("Invalid wall depth\n"), 0);
	*elem = ft_strndup(info - 2, float_len + 2);
	return (1);
}

static int	get_map_infos(t_tile *tile, char *info, char **elem, int elem_nb)
{
	int	len_line;

	while (!ft_strchr(" \t", *info))
		info++;
	while (ft_strchr(" \t", *info))
		info++;
	if (elem_nb == 7)
	{
		if (*info == '1')
			*elem = ft_strndup("1", 1);
		return (1);
	}
	if (elem_nb == 6)
		return (get_wall_depth(info, elem, 0));
	else if ((elem_nb <= 5) && ft_isnum(*info))
		return (get_rgb(tile, info, elem_nb));
	len_line = ft_strclen(info, '\n');
	if (len_line < 4)
		return (ft_error("No informations for an elem.\n"), 0);
	*elem = ft_strndup(info, len_line);
	return (path_is_valid(*elem));
}

/* check if the elements are valid and get them */
/* get the valid elements in the structure */
int	check_single_elem(char *file_infos, int *i,
		char *elems[], t_tile *tile)
{
	int	j;
	int	count;

	j = 0;
	count = 6;
	while (file_infos[*i] && count)
	{
		while (ft_strchr("\n\r \t", file_infos[*i]))
			(*i)++;
		if (!(file_infos[*i] && !ft_strncmp(file_infos + *i, elems[j],
					ft_strlen(elems[j]))
				&& ft_strchr(" \t", file_infos[*i + ft_strlen(elems[j])])))
			return (ft_error("Elements aren't in right order.\n"), 0);
		if (!get_map_infos(tile, file_infos + *i, get_elem(tile, j), j))
			return (0);
		j++;
		count--;
		while (file_infos[*i] && file_infos[*i] != '\n')
			(*i)++;
	}
	if (!count || (count == 1 && !get_elem(tile, 7)))
		return (1);
	return (ft_error("Lacking elements for map.\n"), 0);
}

int	check_elems(char *file_infos, char *elems[], t_tile *tile)
{
	int	i;
	int	j;
	int	count;

	j = 0;
	i = 0;
	count = 8;
	while (file_infos[i] && count)
	{
		while (ft_strchr("\n\r \t", file_infos[i]))
			i++;
		if (!(file_infos[i] && !ft_strncmp(file_infos + i, elems[j],
					ft_strlen(elems[j]))
				&& ft_strchr(" \t", file_infos[i + ft_strlen(elems[j])])))
			return (ft_error("Elements aren't in right order.\n"), 0);
		if (!get_map_infos(tile, file_infos + i, get_elem(tile, j), j))
			return (0);
		j++;
		count--;
		while (file_infos[i] && file_infos[i] != '\n')
			i++;
	}
	if (!count || (count == 1 && !(*get_elem(tile, 7))))
		return (1);
	return (ft_error("Lacking elements for map.\n"), 0);
}
