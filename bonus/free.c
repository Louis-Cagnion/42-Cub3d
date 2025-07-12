/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:43:42 by marvin            #+#    #+#             */
/*   Updated: 2025/07/12 19:02:47 by gakarbou         ###   ########.fr       */
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
		else if (i)
		{
			mlx_destroy_image(mlx, tiles[i].tex_list[4].ptr);
			mlx_destroy_image(mlx, tiles[i].tex_list[5].ptr);
		}
		free(tiles[i].tex_list);
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

void	free_game(t_game *game)
{
	free_entities(game->map.entity_list, game->mlx.init);
	free_tiles(game->map.tiles, game->mlx.init, game->map.tile_defined, 256);
	mlx_destroy_image(game->mlx.init, game->raycast.consts->skybox.ptr);
	mlx_destroy_image(game->mlx.init, game->default_tex.ptr);
	free_mlx(&game->mlx);
	free(game->raycast.consts->row_dist_table);
	free(game->raycast.consts);
	free(game->map.map);
	free(game->thread);
	if (game->map.map_array)
		free_array(&game->map.map_array);
	free(game->raycast.cast_infos);
}
