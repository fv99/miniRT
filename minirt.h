/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:07:24 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:40:08 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
#ifdef __linux__
# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#elif __APPLE__
# include "./minilibx-mac-osx/mlx.h"
# include <ApplicationServices/ApplicationServices.h>
#endif

// god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

// # define M_PI 3.14159265358979323846

typedef struct s_float_3
{
	float			x;
	float			y;
	float			z;
}	t_float_3;

typedef struct s_int_3
{
	int				x;
	int				y;
	int				z;
}	t_int_3;

// ambient lighting, lum = brightness, col = color in hex format
typedef struct s_amb
{
	float			lum;
	int				col;
}	t_amb;

// camera, pos = position, vec = 3d normalized vector
typedef struct s_cam
{
	t_float_3		pos;
	t_float_3		vec;
	size_t			fov;
}	t_cam;

// light point, lum = brightness, col = color in hex format
typedef struct s_light
{
	t_float_3		pos;
	float			lum;
	int				col;
}	t_light;

// map holding struct
typedef struct s_map
{
	t_amb			amb;
	t_cam			cam;
	t_light			light;

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
int		render(t_win *win);

// controls.c
int		handle_keypress(int keysym, t_win *win);
int		handle_destroy_notify(t_win *win);
int		print_controls(t_win *win);

// parser.c
t_map   *parser(char *filename);
char 	*sanitize(char *line);
int   	parse_line(t_map *map, char *line);
int		parse_float(char *str, float *num);
int		parse_ulong(char *str, size_t *num);

// parser_scene.c
int 	parse_ambient(t_map *map, char *line);
int		parse_camera(t_map *map, char *line);
int 	parse_light(t_map *map, char *line);
int 	parse_color(char *str, int *col);
int 	parse_xyz_float(char *str, t_float_3 *coord);

// utils_number.c
float	str_to_float(char *str);
int		str_to_int_color(char *str);
int		is_float(char *str);
int		is_ulong(char *str);

// utils_parser.c
int 	open_file(char *filename);
int		is_rt_file(char *filename);
int 	rgb_to_hex(int r, int g, int b);
int 	error_throw(char *msg);

// utils_array.c
void	free_array(char **arr);
void	print_array(char **arr);
int		array_length(char **arr);

// utils_tests.c
int 	test_map(t_map *map);
int 	test_parser(t_map *map);

// utils.c
t_map   *malloc_map();

#endif