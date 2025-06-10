/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 13:25:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <fcntl.h> // open
# include <stdio.h> // printf, perror
# include <unistd.h> // read, write, close
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror
# include <X11/X.h>
# include <X11/keysym.h>

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

//game settings
# ifndef SPEED
#  define SPEED			0.06666f
# endif
# ifndef ROT_SPEED
#  define ROT_SPEED		0.10f
# endif

//window settings
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1500
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	1500
# endif

// Mouse defines
# define LEFT_CLICK		1
# define SCROLL_CLICK	2
# define RIGHT_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# include "bonus/map_bonus.h"
# include "bonus/draw_bonus.h"
# include "bonus/misc_bonus.h"
# include "bonus/player_bonus.h"
# include "bonus/raycast_bonus.h"
# include "bonus/keyboard_bonus.h"
# include "bonus/entities_bonus.h"

typedef struct s_game
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	t_raycast			raycast;
	t_opti_const		consts;
	t_keyboard_control	key_infos;
}	t_game;

//parse and treat file
int			path_is_valid(char *pathname);
char		**get_elem(t_tile *tile, int elem);
int			treat_file(char *map_name, t_game *game);
int			treat_map(char *map, int i, t_game *game);
int			check_single_elem(char *file_infos, int *i,
				char *elems[], t_tile *tile);
int			check_limits(char **map_array, int map_height,
				int *len_strings, t_tile tiles[256]);
int			check_elems(char *file_infos, char *elem[], t_tile *tile);
int			get_tiles(char *content, int *i, char *elems[], t_map *map);

//player
int			only_one_player(t_game *game);
void		actualise_player_pos(char **map_array, t_player *ptr_p,
				int key, t_tile tiles[256]);

//print
int			usage_prompt(void);
void		ft_error(char *msg);

//display utils
void		put_texture(t_game *game, int *addr,
				t_raycast *infos, int size_line);
void		store_textures(t_map *map, void *mlx);
void		update_player_ray_dirs(t_player *player);
int			get_pixel_color(t_img *img, int x, int y);
void		init_raycast(t_game *game, t_raycast *raycast);
void		put_pixel(t_img *img, int x, int y, int color);
double		get_wall_dist(t_player player, t_raycast *infos,
				double cam_x, t_map map);
void		display_screen(t_game *game, t_opti_const consts,
				t_raycast infos);

//floor and ceil
void		draw_ceil_and_floor_tex(int *addr, int size,
				t_map map, t_raycast *ray);

//entities
void		draw_sprites(t_raycast infos, t_game *game);
void		update_entities(t_list *entities, t_player player,
				t_opti_const consts);
t_entity	*create_entity(char *tex_path, double x, double y, void *mlx_ptr);

//mlx
int			set_mlx(t_mlx *mlx, char *win_title);

//controls
void		init_hooks(t_game *game);
int			key_pressed_check_camera(t_player *player,
				t_keyboard_control key_infos);
int			key_pressed_check_controls(t_game *game, t_player *player);

//free
void		free_mlx(t_mlx *mlx);
void		free_game(t_game *game);

//fucking libft
void		ft_lstclear(t_list **lst, void (*del)(void *));

#endif
