/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:43:42 by marvin            #+#    #+#             */
/*   Updated: 2025/06/09 18:10:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_mlx(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->init, mlx->img);
	if (mlx->window)
		mlx_destroy_window(mlx->init, mlx->window);
	if (mlx->init)
	{
		mlx_destroy_display(mlx->init);
		free(mlx->init);
	}
}

static void	free_map(t_map *map, void *mlx)
{
	if (map->no_path)
		ft_free(&map->no_path);
	if (map->so_path)
		ft_free(&map->so_path);
	if (map->we_path)
		ft_free(&map->we_path);
	if (map->ea_path)
		ft_free(&map->ea_path);
	if (map->map)
		ft_free(&map->map);
	if (map->map_array)
		free_array(&map->map_array);
	if (map->floor_path)
		free(map->floor_path);
	if (map->ceil_path)
		free(map->ceil_path);
	if (!map->tex_list)
		return ;
	mlx_destroy_image(mlx, map->tex_list[0].ptr);
	mlx_destroy_image(mlx, map->tex_list[1].ptr);
	mlx_destroy_image(mlx, map->tex_list[2].ptr);
	mlx_destroy_image(mlx, map->tex_list[3].ptr);
	mlx_destroy_image(mlx, map->tex_list[4].ptr);
	mlx_destroy_image(mlx, map->tex_list[5].ptr);
	free(map->tex_list);
}

static void	free_entities(t_list *entity_list, void *mlx)
{
	t_list		*temp;
	t_entity	*cur;
	int			x;

	while (entity_list)
	{
		temp = entity_list;
		entity_list = entity_list->next;
		x = -1;
		cur = (t_entity *)temp->data;
		while (cur->invisible_parts[++x])
			ft_lstclear(&cur->invisible_parts[x], free);
		mlx_destroy_image(mlx, cur->tex.ptr);
		free(cur->invisible_parts);
		free(temp->data);
		free(temp);
	}
}

void	free_game(t_game *game)
{
	mlx_destroy_image(game->mlx.init, game->map.minimap.img);
	free_entities(game->map.entity_list, game->mlx.init);
	free_map(&game->map, game->mlx.init);
	free_mlx(&game->mlx);
	free(game->raycast.z_buffer);
	free(game->raycast.row_dist_table);
}
