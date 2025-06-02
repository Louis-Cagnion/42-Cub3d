/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:43:42 by marvin            #+#    #+#             */
/*   Updated: 2025/06/01 19:47:43 by gakarbou         ###   ########.fr       */
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

static void	free_tiles(t_tile tiles[256], void *mlx, char *defined, int i)
{
	while (i--)
	{
		if (!defined[i])
			continue ;
		free(tiles[i].no_path);
		free(tiles[i].so_path);
		free(tiles[i].we_path);
		free(tiles[i].ea_path);
		free(tiles[i].floor_path);
		free(tiles[i].ceil_path);
		if (tiles[i].is_wall_str)
		{
			mlx_destroy_image(mlx, tiles[i].tex_list[0].ptr);
			mlx_destroy_image(mlx, tiles[i].tex_list[1].ptr);
			mlx_destroy_image(mlx, tiles[i].tex_list[2].ptr);
			mlx_destroy_image(mlx, tiles[i].tex_list[3].ptr);
		}
		else
		{
			mlx_destroy_image(mlx, tiles[i].tex_list[4].ptr);
			mlx_destroy_image(mlx, tiles[i].tex_list[5].ptr);
		}
		free(tiles[i].tex_list);
	}
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
	free_entities(game->map.entity_list, game->mlx.init);
	free_tiles(game->map.tiles, game->mlx.init, game->map.tile_defined, 256);
	free_mlx(&game->mlx);
	free(game->map.map);
	if (game->map.map_array)
		free_array(&game->map.map_array);
	free(game->raycast.z_buffer);
	free(game->raycast.row_dist_table);
}
