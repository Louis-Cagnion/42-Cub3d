/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 12:13:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_BONUS_H
# define TEXTURES_BONUS_H

typedef struct s_texture
{
	void		*ptr;
	char		*data;
	int			endian;
	int			tex_endian;
	int			size_line;
	int			bpp;
	int			fake_bpp;
	int			fake_size_line;
	int			width;
	double		d_width;
	double		d_height;
	int			height;
}	t_texture;

#endif