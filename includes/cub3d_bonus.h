/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/05/31 17:17:04 by marvin           ###   ########.fr       */
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
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/keysym.h>

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

//game settings
# ifndef SPEED
#  define SPEED			0.06666f / 2
# endif
# ifndef ROT_SPEED
#  define ROT_SPEED		0.10f / 4
# endif

//window settings
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1200
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	1000
# endif

// Mouse defines
# define LEFT_CLICK		1
# define SCROLL_CLICK	2
# define RIGHT_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

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
}	t_keyboard_control;

typedef struct s_raycast
{
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
}	t_sprite_drawing;

typedef struct s_map
{
	t_player	*player;
	t_texture	*tex_list;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_path;
	char		*ceil_path;
	int			f_rgb;
	int			c_rgb;
	char		*map;
	char		**map_array;
	int			w_map;
	int			h_map;
	t_list		*entity_list;
}	t_map;

typedef struct s_mouse
{
	int			delta_x;
	Display		*display;
	Window		window;
	char		ignore_next;
}	t_mouse;

typedef struct s_game
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	t_raycast			raycast;
	t_opti_const		consts;
	t_keyboard_control	key_infos;
	t_mouse				mouse;
}	t_game;

//parse and treat file
int			path_is_valid(char *pathname);
char		**get_elem(t_map *map, int elem);
int			treat_file(char *map_name, t_game *game);
int			treat_map(char *map, int i, t_game *game);

//player
int			only_one_player(t_game *game);
void		actualise_player_pos(char **map_array, t_player *ptr_p, int key);
int			is_valid_move(char **map_array, t_player p, int key);

//print
int			usage_prompt(void);
void		ft_error(char *msg);

//debug
void		print_map(t_map *map);

//display utils
void		store_textures(t_map *map, void *mlx);
void		display_screen(t_game *game, t_opti_const consts,
				t_mlx mlx, t_raycast infos);
void		put_texture(t_game *game, int *addr,
				t_raycast *infos, int size_line);
double		get_wall_dist(t_player player, t_raycast *infos,
				double cam_x, char **map);
void		put_pixel(t_img *img, int x, int y, int color);
int			get_pixel_color(t_img *img, int x, int y);
void		init_size_line_steps(int size_line, int steps[5]);
void		init_raycast(t_game *game, t_raycast *raycast);
void		update_player_ray_dirs(t_player *player);

//entities
t_entity	*create_entity(char *tex_path, double x, double y, void *mlx_ptr);
void		draw_sprites(t_raycast infos, t_game *game);
void		update_entities(t_list *entities, t_player player,
				t_opti_const consts);

//mlx
int			set_mlx(t_mlx *mlx, char *win_title);

//controls
void		init_hooks(t_game *game);
int			mouse_move(int x, int y, t_game *game);
void		key_pressed_check_controls(t_game *game, t_player *player);
int			key_pressed_check_camera(t_player *player,
			t_keyboard_control key_infos);
void		actualise_cam_mouse(t_mouse *mouse, int mid_width, t_player *player);

//debug
void		print_map(t_map *map);

//free
void		free_mlx(t_mlx *mlx);
void		free_game(t_game *game);

//fucking libft
void		ft_lstclear(t_list **lst, void (*del)(void *));

#endif
