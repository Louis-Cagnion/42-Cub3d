/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:29:31 by gakarbou          #+#    #+#             */
/*   Updated: 2025/05/10 14:39:02 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av)
{
	int		len_file;
	t_game	game;

	if (ac == 2)
	{
		game = (t_game){0};
		len_file = ft_strlen(av[1]);
		if (len_file <= 4 || ft_strcmp(av[1] + (len_file - 4), ".cub"))
			return (ft_error("file with '.cub' extension needed.\n"), 1);
		if (treat_file(av[1], &game) || set_mlx(&game.mlx, "Cub3d"))
		{
			free_game(&game);
			return (1);
		}
		store_textures(&game.map, game.mlx.init);
		init_hooks(&game);
		mlx_loop(game.mlx.init);
		free_game(&game);
		return (0);
	}
	usage_prompt();
	return (1);
}
