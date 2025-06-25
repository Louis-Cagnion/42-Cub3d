/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:57:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/25 18:01:32 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_texture	create_skybox(char *path, void *mlx)
{
	t_texture	dest;
	t_texture	temp;

	if (path)
	{
		temp = mlx_xpm_file_to_image(mlx, path, &temp.width, &temp.height);
		temp.data = mlx_get_data_addr(temp.ptr, &dest.bpp, &dest.size_line, &dest.endian);
	}
	else
	{
		temp = mlx_new_image(mlx, 1, 1);
		temp.data = mlx_get_data_addr(temp.ptr, &dest.bpp, &dest.size_line, &dest.endian);
		*(int *)temp.data = 0;
	}
	dest = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);

}
