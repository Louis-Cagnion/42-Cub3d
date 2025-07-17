/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/13 15:15:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (y < 0)
		return ;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_pixel_color(t_img *img, int x, int y)
{
	return (*(int *)(img->data + (y * img->size_line + x * (img->bpp / 8))));
}
