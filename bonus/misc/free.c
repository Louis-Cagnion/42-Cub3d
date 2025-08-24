/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:43:42 by marvin            #+#    #+#             */
/*   Updated: 2025/08/24 17:51:47 by gakarbou         ###   ########.fr       */
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

static void	free_tile(t_tile tile)
{
	free(tile.no_path);
	free(tile.so_path);
	free(tile.we_path);
	free(tile.ea_path);
	free(tile.floor_path);
	free(tile.ceil_path);
}

static void	free_tiles(t_tile tiles[256], char *defined, t_map *map, void *mlx)
{
	int			i;
	t_list		*cur;
	t_list		*temp;

	if (defined[0])
	{
		free_tile(tiles[0]);
		free(tiles['0'].tex_list);
		free(tiles['1'].tex_list);
	}
	else
	{
		i = 256;
		while (i--)
		{
			if (!defined[i])
				continue ;
			free_tile(tiles[i]);
			if (!tiles[i].tex_list)
			{
				free(tiles[i].is_wall_str);
				free(tiles[i].is_door_str);
			}
			free(tiles[i].tex_list);
		}
	}
	ft_lstclear(&map->name_lst, free);
	cur = map->tex_ptr;
	while (cur)
	{
		temp = cur;
		free(((t_texture *)cur->data)->stripe_is_opaque);
		mlx_destroy_image(mlx, ((t_texture *)cur->data)->ptr);
		free(cur->data);
		cur = cur->next;
		free(temp);
	}
}

static void	free_frame(t_list *frame_ptr, void *mlx_ptr)
{
	t_sprite_frame	*frame;
	int				x;

	x = -1;
	frame = (t_sprite_frame *)frame_ptr->data;
	while (frame->invisible_parts[++x])
		ft_lstclear(&frame->invisible_parts[x], free);
	free(frame->invisible_parts);
	mlx_destroy_image(mlx_ptr, frame->tex.ptr);
	free(frame);
	free(frame_ptr);
}

static void	free_entities(t_list *entity_list, void *mlx)
{
	t_list			*temp;
	t_list			*cur_frame;
	t_list			*temp_frame;
	t_entity		*cur;

	while (entity_list)
	{
		temp = entity_list;
		entity_list = entity_list->next;
		cur = (t_entity *)temp->data;
		cur_frame = cur->frame_list;
		while (cur_frame != cur->first_frame)
			cur_frame = cur_frame->next;
		cur_frame = cur_frame->next;
		while (cur_frame != cur->first_frame)
		{
			temp_frame = cur_frame;
			cur_frame = cur_frame->next;
			free_frame(temp_frame, mlx);
		}
		free_frame(cur_frame, mlx);
		free(temp->data);
		free(temp);
	}
}

void	free_game(t_game *game, int mode)
{
	free_entities(game->map.entity_list, game->mlx.init);
	free_tiles(game->map.tiles, game->map.tile_defined, &game->map, game->mlx.init);
	ft_lstclear(&game->map.name_lst, free);
	if (mode)
	{
		mlx_destroy_image(game->mlx.init, game->raycast.consts->skybox.ptr);
		mlx_destroy_image(game->mlx.init, game->map.minimap.mini_img);
		mlx_destroy_image(game->mlx.init, game->map.minimap.player_img);
		mlx_destroy_image(game->mlx.init, game->default_tex.ptr);
		free(game->raycast.consts->row_dist_table);
		free(game->raycast.consts);
		free(game->raycast.cast_infos);
	}
	free(game->map.map);
	free_mlx(&game->mlx);
	free(game->thread);
	free_array(&game->map.door_array);
	if (game->map.map_array)
		free_array(&game->map.map_array);
}
