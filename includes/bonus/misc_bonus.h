/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:01:51 by locagnio          #+#    #+#             */
/*   Updated: 2025/06/10 13:56:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISC_BONUS_H
# define MISC_BONUS_H

# include "mlx_int.h"

typedef struct s_opti_const
{
	double		float_width;
	double		cam_coef;
	int			half_height;
	int			half_width;
}	t_opti_const;

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

#endif