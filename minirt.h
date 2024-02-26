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
# include <fcntl.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

// god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

# define M_PI 3.14159265358979323846

typedef struct s_float_3
{
	float			x;
	float			y;
	float			z;
}	t_float_3;

// ambient lighting, lum = brightness, col = color in hex format
typedef struct s_amb
{
	float			lum;
	int				col;
}	t_amb;

// camera, pos = position, vec = 3d normalized vector
typedef struct s_cam
{
	t_float_3		*pos;
	t_float_3		*vec;
	int				fov;
}	t_cam;

// light point, lum = brightness, col = color in hex format
typedef struct s_light
{
	t_float_3		*pos;
	float			lum;
	int				col;
}	t_light;

// map holding struct
typedef struct s_map
{
	t_amb			*amb;
	t_cam			*cam;
	t_light			*light;

	// objects will go here, have to figure out data structure

}	t_map;

// main window holding struct
typedef struct s_win
{
	void			*mlx;
	void			*win;
	void			*img;
}	t_win;

// minirt.c
int		render_background(t_win *win);

// controls.c
int		handle_keypress(int keysym, t_win *win);
int		handle_destroy_notify(t_win *win);
int		print_controls(t_win *win);

// parser_utils.c
int 	open_file(char *filename);
int 	rgb_to_hex(int r, int g, int b);
int 	test_map(t_map *map);
int 	test_parser(t_map *map);

// parser.c
t_map   parser(char *filename);




#endif