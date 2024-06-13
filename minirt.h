/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:07:24 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 20:53:31 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

#ifdef __linux__
# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

enum e_keycodes
{
	KEY_A = 97,
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_M = 109,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_U = 117,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Y = 121,
	KEY_Z = 122,
	KEY_ESC = 65307,
	KEY_SPACE = 32,
	KEY_SLASH = 47,
	KEY_L_SHIFT = 65505,
	KEY_R_SHIFT = 65506,
	KEY_R_CTRL = 65508,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_DOT = 46,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 59,
	KEY_COMMAND = 65507,
	KEY_BACKSPACE = 65288,
};

#elif __APPLE__
# include "./minilibx-mac-osx/mlx.h"
# include <ApplicationServices/ApplicationServices.h>

enum e_keycodes
{
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_SLASH = 44,
	KEY_L_SHIFT = 257,
	KEY_R_SHIFT = 258,
	KEY_R_CTRL = 269,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOT = 47,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 41,
	KEY_COMMAND = 259,
	KEY_BACKSPACE = 51,
};

#endif

// god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

// samples per pixel
# define SAMPLES_PP 8192

# define M_PI 3.14159265358979323846

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

// mandatory parts of scene below (only 1 per file)
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

// objects in scene (linked list)
// spheres - pos = sp center coords, dia = diameter, col = color in hex format
typedef struct s_sp
{
	t_float_3		pos;
	float			dia;
	int				col;
	struct s_sp		*next;
}	t_sp;

// planes - pos = xyz coords of a point in plane
// vec = 3d normalized vector in range -1, 1, col = color in hex format
typedef struct s_pl
{
	t_float_3		pos;
	t_float_3		vec;
	int				col;
	struct s_pl		*next;
}	t_pl;

// cylinders - pos = xyz coords of center
// vec = 3d normalized vector of axis in range -1, 1
// dia = diameter, col = color in hex format
typedef struct s_cy
{
	t_float_3		pos;
	t_float_3		vec;
	float			dia;
	float			hth;
	int				col;
	struct s_cy		*next;
}	t_cy;

// main map holding struct
typedef struct s_map
{
	t_amb			amb;
	t_cam			cam;
	t_light			light;

	t_sp			*spheres;
	t_pl			*planes;
	t_cy			*cylinders;
}	t_map;

typedef struct s_ray
{
	t_float_3		orig;
	t_float_3		dir;
}	t_ray;

typedef struct s_scene
{
	float			scale;
	float			aspect_ratio;
}	t_scene;

// main holding struct
typedef struct s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	
	char			*addr;
	int				bpp;
	int				line_l;
	int				endian;

	t_map			*map;
	t_scene			scene;
}	t_win;

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

// parser_objects.c
int		parse_sphere(t_map *map, char *line);
int		parse_plane(t_map *map, char *line);
int 	parse_cylinder(t_map *map, char *line);

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
int 	test_map(int fd);
int 	test_parser(t_map *map);

// utils_mem.c
t_map   *malloc_map();
void 	free_spheres(t_sp *spheres);
void 	free_planes(t_pl *planes);
void 	free_cylinders(t_cy *cylinders);
void 	free_objects(t_map *map);

// utils_vec.c
t_float_3	vec_sub(t_float_3 a, t_float_3 b);
t_float_3	vec_add(t_float_3 a, t_float_3 b);
t_float_3	vec_mul(t_float_3 a, float b);
t_float_3	vec_div(t_float_3 a, float b);
float		vec_dot(t_float_3 a, t_float_3 b);

// utils_vec2.c
t_float_3	vec_normalize(t_float_3 v);
t_float_3   vec_scale(t_float_3 vec, float scale);
int create_color(float r, float g, float b);


// render.c
int 		trace_ray(t_ray ray, t_map *map, int *color);
void		render_ray(t_win *win, int x, int y);
int			render(t_win *win);
int			sphere_intersect(t_ray ray, t_sp *sphere, float *t);

#endif