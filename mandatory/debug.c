/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:16:37 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/24 21:04:17 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map *m)
{
	if (!m)
		return ;
	if (m->no_path)
		printf("no_path = %s\n", m->no_path);
	else
		printf("no_path = (null)\n");
	if (m->so_path)
		printf("so_path = %s\n", m->so_path);
	else
		printf("so_path = (null)\n");
	if (m->we_path)
		printf("we_path = %s\n", m->we_path);
	else
		printf("we_path = (null)\n");
	if (m->ea_path)
		printf("ea_path = %s\n", m->ea_path);
	else
		printf("ea_path = (null)\n");
	printf("f_rgb = {%d, %d, %d}\n", m->f_rgb[0], m->f_rgb[1], m->f_rgb[2]);
	printf("c_rgb = {%d, %d, %d}\n", m->c_rgb[0], m->c_rgb[1], m->c_rgb[2]);
	printf("h_map = %d\nw_map = %d\n", m->h_map, m->w_map);
	if (m->map)
		printf("map :\n%s\n", m->map);
	else
		printf("map = (null)\n");
	if (m->map_array)
	{
		printf("map_array :\n");
		print_array(m->map_array);
	}
	else
		printf("map = (null)\n");
}
