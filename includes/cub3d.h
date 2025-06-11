/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/05/18 15:03:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
#  define SPEED			0.06666
# endif
# ifndef ROT_SPEED
#  define ROT_SPEED		0.10
# endif

//window settings
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1280
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	720
# endif

// Mouse defines
# define LEFT_CLICK		1
# define SCROLL_CLICK	2
# define RIGHT_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

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
	char		side;
	int			line_height;
	int			half_line_height;
	int			wall_pos[2];
	double		ray_dir[2];
	double		wall_dist;
	int			texture_x;
	int			size_line;
	int			*addr;
	int			half_win_height;
}	t_raycast;

typedef struct s_opti_const
{
	double	float_width;
	double	cam_coef;
	int		half_height;
}	t_opti_const;

typedef struct s_texture
{
	void			*ptr;
	char			*data;
	int				endian;
	int				tex_endian;
	int				size_line;
	int				bpp;
	int				fake_bpp;
	int				width;
	double			d_width;
	int				height;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	plane_x;
	double	plane_y;
	double	direction_x;
	double	direction_y;
	double	mvt_speed;
}	t_player;

typedef struct s_map
{
	t_texture	*tex_list;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f_rgb;
	int			c_rgb;
	char		*map;
	char		**map_array;
	int			w_map;
	int			h_map;
}	t_map;

typedef struct s_game
{
	t_mlx				mlx;
	t_map				map;
	t_player			player;
	t_opti_const		consts;
	t_keyboard_control	key_infos;
}	t_game;

//parse and treat file
int		path_is_valid(char *pathname);
char	**get_elem(t_map *map, int elem);
int		treat_file(char *map_name, t_game *game);
int		treat_map(char *map, int i, t_game *game);

//player
int		only_one_player(t_game *game);
void	actualise_player_pos(char **map_array, t_player *ptr_p, int key);
int		is_valid_move(char **map_array, t_player p, int key);

//print
int		usage_prompt(void);
void	ft_error(char *msg);

//debug
void	print_map(t_map *map);

//display utils
void	store_textures(t_map *map, void *mlx);
void	display_screen(t_game *game, t_opti_const consts, t_mlx mlx);
void	put_texture(t_game *game, int *addr, t_raycast *infos, int size_line);
double	get_wall_dist(t_player player, t_raycast *infos,
			double cam_x, char **map);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_pixel_color(t_img *img, int x, int y);
void	init_size_line_steps(int size_line, int steps[5]);

//mlx
int		set_mlx(t_mlx *mlx, char *win_title);

//controls
void	init_hooks(t_game *game);
void	key_pressed_check_controls(t_game *game);
int		key_pressed_check_camera(t_game *game);

//debug
void	print_map(t_map *map);

//free
void	free_mlx(t_mlx *mlx);
void	free_game(t_game *game);

#endif
