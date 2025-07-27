/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:53:48 by locagnio          #+#    #+#             */
/*   Updated: 2025/07/27 16:12:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**get_elem(char *elem_s, t_tile *tile, int *j)
{
	if (!ft_strncmp(elem_s, "NO", 2) || ft_iswhitespace(elem_s[2]))
		return (*j = 0, &tile->no_path);
	else if (!ft_strncmp(elem_s, "SO", 2) || ft_iswhitespace(elem_s[2]))
		return (*j = 1, &tile->so_path);
	else if (!ft_strncmp(elem_s, "WE", 2) || ft_iswhitespace(elem_s[2]))
		return (*j = 2, &tile->we_path);
	else if (!ft_strncmp(elem_s, "EA", 2) || ft_iswhitespace(elem_s[2]))
		return (*j = 3, &tile->ea_path);
	else if (!ft_strncmp(elem_s, "F", 1) || ft_iswhitespace(elem_s[1]))
		return (*j = 4, &tile->floor_path);
	else if (!ft_strncmp(elem_s, "C", 1) || ft_iswhitespace(elem_s[1]))
		return (*j = 5, &tile->ceil_path);
	else if (!ft_strncmp(elem_s, "W", 1) || ft_iswhitespace(elem_s[1]))
		return (*j = 6, &tile->is_wall_str);
	return (*j = -1, NULL);
}

int	path_is_valid(char *pathname)
{
	int		fd;
	int		bytes_read;
	char	test_buffer[10];

	pathname[ft_strlen(pathname) - ft_strrspn(pathname, WSPACES)] = 0;
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
