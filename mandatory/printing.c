/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:56:33 by locagnio          #+#    #+#             */
/*   Updated: 2025/05/05 16:35:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	usage_prompt(void)
{
	ft_write(2, "Hello there !\nThis program should take a describing scene");
	ft_write(2, " file with '.cub' extension.\n\n The file should only be");
	ft_write(2, " formated with the following characters :\n\t- 0 : For empty");
	ft_write(2, " spaces.\n\t- 1 : For walls. The map should be closed with");
	ft_write(2, " walls.\n\t- N, S, E or W : The starting position");
	ft_write(2, " and orientation of the player. Only one is accepted.\n\t");
	ft_write(2, "- Spaces : You can put spaces to change the shape of the ");
	ft_write(2, "map, if there's spaces inside the\n\t\t   map, they should ");
	ft_write(2, "be surrounded with walls to be valid.\n\n");
	ft_write(2, "For performances and seg fault reasons, the movement speed");
	ft_write(2, " won't exceed 1.\n\n");
	return (1);
}

void	ft_error(char *msg)
{
	ft_write(2, "Error\n");
	ft_write(2, msg);
}
