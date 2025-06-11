/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:53:48 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/11 20:09:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**get_elem(t_tile *tile, int elem)
{
	if (elem == 0)
		return (&tile->no_path);
	else if (elem == 1)
		return (&tile->so_path);
	else if (elem == 2)
		return (&tile->we_path);
	else if (elem == 3)
		return (&tile->ea_path);
	else if (elem == 4)
		return (&tile->floor_path);
	else if (elem == 5)
		return (&tile->ceil_path);
	else if (elem == 6)
		return (&tile->is_wall_str);
	return (NULL);
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
