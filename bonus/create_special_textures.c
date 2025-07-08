/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_special_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:57:22 by gakarbou          #+#    #+#             */
/*   Updated: 2025/07/08 21:40:41 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	resize_image(int *addr, t_texture src, int width,
		int height)
{
	double	steps[2];
	double	tex_y;
	double	tex_x;
	int		*src_addr;
	int		temp_width;

	steps[0] = (double)src.width / width;
	steps[1] = (double)src.height / height;
	tex_y = 0;
	while (height--)
	{
		temp_width = width;
		tex_x = 0;
		src_addr = (int *)(src.data + src.size_line * (int)tex_y);
		while (temp_width--)
		{
			*(addr++) = src_addr[(int)tex_x];
			tex_x += steps[0];
		}
		tex_y += steps[1];
	}
}

t_texture	create_skybox(char *path, void *mlx)
{
	t_texture	dest;
	t_texture	temp;

	temp.ptr = mlx_xpm_file_to_image(mlx, path, &temp.width, &temp.height);
	temp.data = mlx_get_data_addr(temp.ptr, &temp.bpp,
			&temp.size_line, &temp.endian);
	dest.ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
			&dest.size_line, &dest.endian);
	resize_image((int *)dest.data, temp, WIN_WIDTH, WIN_HEIGHT);
	mlx_destroy_image(mlx, temp.ptr);
	return (dest);
}

t_texture	create_default_texture(void *mlx)
{
	t_texture	dest;

	dest.ptr = mlx_new_image(mlx, 2, 2);
	if (dest.ptr)
		dest.data = mlx_get_data_addr(dest.ptr, &dest.bpp,
				&dest.size_line, &dest.endian);
	dest.fake_bpp = dest.bpp >> 3;
	dest.fake_size_line = dest.size_line >> 2;
	dest.tex_endian = dest.endian - 1;
	dest.d_width = 2.0f;
	dest.d_height = 2.0f;
	dest.width = 2;
	dest.height = 2;
	*(int *)dest.data = 0;
	*(int *)(dest.data + 4) = 0xff00dc;
	*(int *)(dest.data + 8) = 0xff00dc;
	*(int *)(dest.data + 12) = 0;
	return (dest);
}
