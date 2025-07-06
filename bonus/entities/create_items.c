/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:18:08 by marvin            #+#    #+#             */
/*   Updated: 2025/07/06 20:23:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_items	create_item(char *name, int item_value, t_mlx mlx)
{
	t_items	item;

	item.name = name;
	item.value = item_value;
	item.item_img = mlx_new_image(mlx.init, /*  */0, /*  */0);
	//put pixels on it with dark magic i'm not aware of
	return (item);
}
