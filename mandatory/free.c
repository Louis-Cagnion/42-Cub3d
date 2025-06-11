/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:43:42 by marvin            #+#    #+#             */
/*   Updated: 2025/05/06 05:46:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!map->tex_list)
		return ;
	mlx_destroy_image(mlx, map->tex_list[0].ptr);
	mlx_destroy_image(mlx, map->tex_list[1].ptr);
	mlx_destroy_image(mlx, map->tex_list[2].ptr);
	mlx_destroy_image(mlx, map->tex_list[3].ptr);
	free(map->tex_list);
}

void	free_game(t_game *game)
{
	free_map(&game->map, game->mlx.init);
	free_mlx(&game->mlx);
}
