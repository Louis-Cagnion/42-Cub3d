/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/10 13:41:11 by marvin           ###   ########.fr       */
=======
/*   Updated: 2025/06/10 13:29:33 by marvin           ###   ########.fr       */
>>>>>>> main
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

<<<<<<< HEAD
//player
# ifndef P_HPS
#  define P_HPS		100
# endif
# ifndef P_ATK
#  define P_ATK		50
# endif

//player
# ifndef E_HPS
#  define E_HPS		P_ATK
# endif
# ifndef E_ATK
#  define E_ATK		P_HPS / 5
# endif

typedef struct s_inv_size
{
	int		start;
	int		end;
}	t_inv_size;

typedef struct s_mlx
{
	void		*init;
	void		*window;
	t_img		*img;
	int			size_line;
}	t_mlx;

typedef struct s_keyboard_control
{
	char		w_key;
	char		a_key;
	char		s_key;
	char		d_key;
	char		left_key;
	char		right_key;
	char		up_key;
	char		down_key;
}	t_keyboard_control;

typedef struct s_raycast
{
	int			tile;
	int			*addr;
	char		side;
	int			line_height;
	int			half_line_height;
	int			wall_pos[2];
	double		ray_dir[2];
	double		wall_dist;
	int			texture_x;
	int			size_line;
	int			fake_bpp;
	int			tex_fake_bpp;
	double		*row_dist_table;
	int			half_win_height;
	double		cam_x;
	int			cam_y;
	double		cam_x_step;
	double		*z_buffer;
}	t_raycast;

typedef struct s_opti_const
{
	double		float_width;
	double		cam_coef;
	int			half_height;
	int			half_width;
}	t_opti_const;

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

typedef struct s_stats
{
	int	hps;
	int	attack;
} t_stats;

typedef struct s_entity
{
	double		x;
	double		y;
	double		player_dist_x;
	double		player_dist_y;
	double		player_dist;
	double		draw_dir_x;
	double		draw_dir_y;
	int			screen_x;
	int			sprite_height;
	int			half_height;
	int			framerate;
	t_list		**invisible_parts;
	t_texture	tex;
	t_stats		stats;
}	t_entity;

typedef struct s_player
{
	double		x;
	double		y;
	int			int_x;
	int			int_y;
	double		x_mantissa;
	double		y_mantissa;
	double		plane_x;
	double		plane_y;
	double		direction_x;
	double		direction_y;
	double		ray_dir_x[2];
	double		ray_dir_y[2];
	double		mvt_speed;
	double		inv_deter;
	int			cam_y;
	int			half_win_height;
	t_stats		stats;
}	t_player;

typedef struct s_sprite_drawing
{
	double		step;
	double		ratio;
	int			delim_x_start;
	int			delim_x_end;
	int			delim_y_start;
	int			delim_y_end;
	double		start_tex_y;
	int			screen_x;
	int			sprite_height;
	double		tex_y;
	int			*tex_addr;
	int			*addr;
	int			cam_y;
}	t_sprite_drawing;

typedef struct s_tile
{
	t_texture	*tex_list;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_path;
	char		*ceil_path;
	char		*is_wall_str;
	int			f_rgb;
	int			c_rgb;
	int			is_wall;
}	t_tile;

typedef struct s_plane_drawer
{
	double	ray_dirs[2];
	double	player_pos[2];
	double	floor_pos[2];
	double	real_pos[2];
	int		map_pos[2];
	double	*row_table;
	int		tile;
}	t_plane_drawer;

typedef struct s_map
{
	t_texture	*tex_list;
	t_player	*player;
	t_tile		tiles[256];
	char		tile_defined[256];
	char		*map;
	char		**map_array;
	int			w_map;
	int			h_map;
	t_list		*entity_list;
}	t_map;
=======
# include "bonus/map_bonus.h"
# include "bonus/draw_bonus.h"
# include "bonus/misc_bonus.h"
# include "bonus/player_bonus.h"
# include "bonus/raycast_bonus.h"
# include "bonus/entities_bonus.h"
>>>>>>> main

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
void		display_stats(t_stats p_stats, t_mlx mlx);
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
