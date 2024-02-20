/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:07:24 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/02/20 19:25:33 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

// god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// main data holding struct
typedef struct s_win
{
	void		*mlx;
	void		*win;
	void		*img;
}	t_win;

// minirt.c
int		render_background(t_win *win);

// controls.c
int		handle_keypress(int keysym, t_win *win);
int		handle_destroy_notify(t_win *win);
int		print_controls(t_win *win);


#endif