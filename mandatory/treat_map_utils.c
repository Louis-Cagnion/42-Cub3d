/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:57:47 by gakarbou          #+#    #+#             */
/*   Updated: 2025/08/24 19:36:33 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check the 9 boxs around a space and see if it's surrounded with 1 or spaces*/
static int	walls_around(int *len_strings, char **map_array, int i, char *walls)
{
	static int	j = -1;

	if (i == -1)
		return (j++);
	if ((map_array[j + 1] && i < len_strings[j + 1]
			&& !ft_strchr(walls, map_array[j + 1][i]))
	|| (map_array[j + 1] && i + 1 < len_strings[j + 1]
		&& !ft_strchr(walls, map_array[j + 1][i + 1]))
	|| (map_array[j + 1] && i > 0 && i - 1 < len_strings[j + 1]
		&& !ft_strchr("1", map_array[j + 1][i - 1]))
	|| (j > 0 && i < len_strings[j - 1]
		&& !ft_strchr(walls, map_array[j - 1][i]))
	|| (j > 0 && i + 1 < len_strings[j - 1]
		&& !ft_strchr(walls, map_array[j - 1][i + 1]))
	|| (j > 0 && i > 0 && i - 1 < len_strings[j - 1]
		&& !ft_strchr(walls, map_array[j - 1][i - 1]))
	|| (map_array[j][i] && map_array[j][i + 1]
		&& !ft_strchr(walls, map_array[j][i + 1]))
	|| (i > 0
		&& !ft_strchr(walls, map_array[j][i - 1])))
		return (0);
	return (1);
}

/* if a space is not surrounded by the limits of the map, it return 0 */
int	check_limits(char **map_array, int map_height,
		int *len_strings)
{
	int		i;
	int		j;

	j = 0;
	while (j < map_height)
	{
		i = 0;
		walls_around(NULL, NULL, -1, NULL);
		while (map_array[j][i])
		{
			if (map_array[j][i] == ' '
				&& !walls_around(len_strings, map_array, i, "! "))
				return (0);
			i++;
			if (!map_array[j][i] && !walls_around(len_strings,
						map_array, i, "! "))
				return (0);
		}
		j++;
	}
	return (1);
}
