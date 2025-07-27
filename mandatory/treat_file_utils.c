/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:53:48 by locagnio          #+#    #+#             */
/*   Updated: 2025/07/27 16:53:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_elem(char *elem_s, t_map *map, int *j)
{
	if (!ft_strncmp(elem_s, "NO", 2) && ft_iswhitespace(elem_s[2]))
		return (*j = 0, &map->no_path);
	else if (!ft_strncmp(elem_s, "SO", 2) && ft_iswhitespace(elem_s[2]))
		return (*j = 1, &map->so_path);
	else if (!ft_strncmp(elem_s, "WE", 2) && ft_iswhitespace(elem_s[2]))
		return (*j = 2, &map->we_path);
	else if (!ft_strncmp(elem_s, "EA", 2) && ft_iswhitespace(elem_s[2]))
		return (*j = 3, &map->ea_path);
	else if (*elem_s == 'F' && ft_iswhitespace(elem_s[1]))
		return (*j = 4, NULL);
	else if (*elem_s == 'C' && ft_iswhitespace(elem_s[1]))
		return (*j = 5, NULL);
	return (*j = -1, NULL);
}

int	path_is_valid(char *pathname)
{
	int		fd;
	int		bytes_read;
	char	test_buffer[10];

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (ft_error("Path for elem is invalid\n"), 0);
	bytes_read = read(fd, test_buffer, sizeof(test_buffer));
	close(fd);
	if (bytes_read == -1)
		return (ft_error("Path for elem is not leading to a file\n"), 0);
	if (!bytes_read)
		return (ft_error("Path for elem leads to empty file\n"), 0);
	return (1);
}
