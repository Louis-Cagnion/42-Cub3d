/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:49:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/06/03 01:58:36 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_entity_framerate(t_entity *entity, int framerate)
{
	entity->framerate = framerate;
}

void	add_entity_frame(t_entity *entity, char *tex_path, void *mlx_ptr)
{
	t_list			*frame;
	t_texture		tex;
	t_list			*cur;

	tex.ptr = mlx_xpm_file_to_image(mlx_ptr, tex_path, &tex.width, &tex.height);
	if (tex.ptr)
		tex.data = mlx_get_data_addr(tex.ptr, &tex.bpp,
				&tex.size_line, &tex.endian);
	tex.tex_endian = tex.endian - 1;
	tex.d_width = (double)tex.width;
	tex.d_height = (double)tex.height;
	tex.fake_size_line = tex.size_line >> 2;
	frame = create_cell(create_sprite_frame(tex));
	cur = entity->frame_list;
	while (cur->next != entity->first_frame)
		cur = cur->next;
	cur->next = frame;
	frame->next = entity->first_frame;
}
