/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 12:23:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/28 17:02:01 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	*init_row_dist_table(int half_height)
{
	double	*table;
	int		i;

	table = malloc(sizeof(double) * WIN_HEIGHT);
	if (!table)
	{
		ft_error("Memory error\n");
		exit(0);
	}
	i = -1;
	while (++i < WIN_HEIGHT)
		table[i] = half_height / (double)i;
	return (table);
}
