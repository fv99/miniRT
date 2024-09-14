/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:07:24 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/14 15:18:11 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

# ifdef __linux__
#  include "./minilibx-linux/mlx.h"
#  include <X11/X.h>
#  include <X11/keysym.h>
# elif __APPLE__
#  include "./minilibx-mac-osx/mlx.h"
#  include <ApplicationServices/ApplicationServices.h>
# endif
# ifdef __linux__

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
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_COMMA = 44,
	KEY_NUMPAD_PLUS = 65451,
	KEY_NUMPAD_MINUS = 65453,
};

# elif __APPLE__

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
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_COMMA = 43,
	KEY_NUMPAD_PLUS = 69,
	KEY_NUMPAD_MINUS = 78,
};

# endif

// math macros
# define PI 3.1415926535f

// god's chosen aspect ratio
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
// change this later
# define NUM_THREADS 8

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_obj_type;

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

// introducing quarternions for rotation
typedef struct s_quat
{
	float			w;
	float			x;
	float			y;
	float			z;
}	t_quat;

// mandatory parts of scene below (only 1 per file)
// ambient lighting, lum = brightness, col = color in hex format
// amb = normalized color (lum * col)
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

// main object holding struct
typedef struct s_obj
{
	t_obj_type		type;
	void			*object;
	int				color;
	int				id;
	struct s_obj	*next;
}	t_obj;

// used in cylinder intersection function
//
// oc = vector from ray origin to cylinder base
// dir_vec = direction vector of the ray
// cyl_vec = normalized axis direction vector of cylinder
// d_cross_a = cross product of d and cylinder axis
// oc_cross_a = cross product of oc and cylinder axis
// quad = coefficients of quadratic equation
// hit_point = point on cyl surface where ray intersects
// hit_base = vector from hit point to the base center of cylinder
// t0, t1 = possible intersection points
// disc = discriminant of quadratic equation
// proj_l = projection of hit_base onto cylinder axis
typedef struct s_cyl_intersect
{
	t_float_3		oc;
	t_float_3		dir_vec;
	t_float_3		cyl_vec;
	t_float_3		d_cross_a;
	t_float_3		oc_cross_a;
	t_float_3		quad;
	t_float_3		hit_point;
	t_float_3		hit_base;
	float			a;
	float			b;
	float			c;
	float			t0;
	float			t1;
	float			disc;
	float			proj_l;
	float			dia;
	int				hit_cap;
	int				hit_side;
}	t_cyl_intersect;

typedef struct s_ray
{
	t_float_3		orig;
	t_float_3		dir;
}	t_ray;

// main map holding struct
typedef struct s_map
{
	t_amb			amb;
	t_cam			cam;
	t_light			light;
	t_obj			*objects;
	float			aspect_ratio;	
	t_float_3		vec_up;
	t_float_3		vec_right;
	float			height;
	float			width;
}	t_map;

typedef struct s_trace
{
	t_obj		hit_object;
	t_ray		ray;
	t_float_3	intersection;
	t_float_3	normal;
	t_float_3	hit_point;
	int			color;
	float		t;
}	t_trace;

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
	int				num_cores;
	t_map			*map;
}	t_win;

typedef struct s_thread
{
	t_win	*win;
	int		start_y;
	int		end_y;
}	t_thread;

// controls.c
int			handle_keypress(int keysym, t_win *win);
void		handle_keypress_with_angle(int keysym, t_win *win);
void		handle_keypress_without_angle(int keysym, t_win *win);
int			handle_destroy_notify(t_win *win);
int			print_controls(t_win *win);

// parser.c
t_map		*parser(char *filename);
char		*sanitize(char *line);
int			parse_line(t_map *map, char *line);
int			parse_float(char *str, float *num);
int			parse_ulong(char *str, size_t *num);

// parser_scene.c
int			parse_ambient(t_map *map, char *line);
int			parse_camera(t_map *map, char *line);
int			parse_light(t_map *map, char *line);
int			parse_color(char *str, int *col);
int			parse_xyz_float(char *str, t_float_3 *coord);

// parser_objects.c
int			parse_sphere(t_map *map, char *line);
int			parse_plane(t_map *map, char *line);
int			parse_cylinder(t_map *map, char *line);

// utils_number.c
float		str_to_float(char *str);
int			str_to_int_color(char *str);
int			is_float(char *str);
int			is_ulong(char *str);

// utils_parser.c
int			open_file(char *filename);
int			is_rt_file(char *filename);
void		add_object(t_map *map, t_obj_type type, void *object, int col);

// utils_array.c
void		free_array(char **arr);
void		print_array(char **arr);
int			array_length(char **arr);

// utils_tests.c
void		draw_gradient(t_win *win);
int			test_map(int fd);
int			test_parser(t_map *map);

// utils_mem.c
t_map		*malloc_map(void);
void		free_objects(t_obj *objects);
int			error_throw(char *msg);

// utils_vec.c
t_float_3	vec_sub(t_float_3 a, t_float_3 b);
t_float_3	vec_add(t_float_3 a, t_float_3 b);
t_float_3	vec_mul(t_float_3 a, float b);
t_float_3	vec_div(t_float_3 a, float b);
t_float_3	vec_scale(t_float_3 v, float scalar); // mozna delete

// utils_vec2.c
float		vec_dot(t_float_3 a, t_float_3 b);
t_float_3	vec_normalize(t_float_3 v);
t_float_3	vec_cross(t_float_3 v1, t_float_3 v2);
int			is_zero_vector(t_float_3 vec);
float		vec_cos(t_float_3 a, t_float_3 b);

// utils_vec3.c
t_float_3	vec_negate(t_float_3 vec);
float		vec_length(t_float_3 vec);

// utils_win.c
int			ambient_lum(t_map *map);
void		pixel_to_img(t_win *win, int x, int y, int color);

// utils_col.c
int			create_color(int r, int g, int b);
int			rgb_to_hex(int r, int g, int b);
int			clamp(int value, int min, int max);
t_int_3		extract_rgb(int col);

// utils_col2.c
int			add_colors(int col1, int col2);
int			color_multiply(int color, float ratio);

// render.c
t_trace		*closest_obj(t_ray ray, t_trace *closest, t_obj *object);
void		render_ray(t_win *win, int x, int y);
void		*threaded_render(void *arg);
int			render(t_win *win);

// render_normal.c
t_float_3	sphere_normal(t_trace *inter);
t_float_3	cylinder_normal(t_trace *inter, t_ray ray);
t_float_3	plane_normal(t_trace *inter, t_ray ray);
t_float_3	shape_normal(t_trace *inter, t_ray ray);

// render_view.c
void		camera_init(t_map *map);
t_float_3	pixels_to_viewport(int x, int y);
t_ray		throw_ray(t_map *map, t_float_3 vec);

// render_intersects.c
int			intersect(t_ray ray, t_obj *obj, float *t);
int			sphere_intersect(t_ray ray, t_sp *sphere, float *t);
int			plane_intersect(t_ray ray, t_pl *plane, float *t);

// render_intersect_cylinders.c
int			cylinder_intersect(t_ray ray, t_cy *cylinder, float *t);
int			is_valid_intersect(t_cyl_intersect *vars, \
t_cy *cylinder, t_ray ray, float *t);
int			hit_cyl_side(t_ray ray, t_cy *cylinder, \
t_cyl_intersect *vars, float *t);
int			hit_cyl_cap(t_ray ray, t_cy *cylinder, \
t_cyl_intersect *vars, float *t);
int			intersect_disk(t_ray ray, t_float_3 disk_center, \
t_cyl_intersect *vars, float *t);

// render_illuminate.c
void		illuminate(t_map *map, t_trace *closest);
int			diffuse(t_map *map, t_trace *closest, float intensity);
int			calculate_shadow(t_map *map, t_trace *closest);
int			obscured(t_map *map, t_ray *ray, t_obj *closest, float max_dist);

// translate_object.c
void		translate_object_x(t_obj *obj, float translation);
void		translate_object_y(t_obj *obj, float translation);
void		translate_object_z(t_obj *obj, float translation);
void		translate_object(t_obj *obj, float translation, char axis);
void		translate_objects(t_win *win, float translation, char axis);

// move_features.c
void		move_objects(t_win *win, int keysym);
void		move_light(t_win *win, int keysym);
void		move_camera(t_win *win, int keysym);

// quaternion.c
t_quat		quaternion_from_axis_angle(t_float_3 axis, float angle);
t_quat		quaternion_normalize(t_quat q);
t_quat		quaternion_multiply(t_quat q1, t_quat q2);
t_float_3	quaternion_rotate_vector(t_quat q, t_float_3 v);
void		perform_rotation(t_cy *cylinder, t_quat q);

// rotation_objects.c
void		perform_plane_rotation(t_pl *plane, t_quat q);
void		perform_cylinder_rotation(t_cy *cylinder, t_quat q);
void		rotate_object(t_obj *obj, t_quat q);
void		rotate_cylinder(t_win *win, int keysym, float angle);
void		rotate_plane(t_win *win, int keysym, float angle);

// rotation_get_axis.c
t_float_3	get_rot_axis_plane(int keysym);
t_float_3	get_rot_axis_cylinder(int keysym);
t_float_3	get_rot_axis_camera(int keysym);

// rotation_camera.c
void		perform_camera_rotation(t_win *win, t_quat q);
void		rotate_camera(t_win *win, int keysym, float angle);

// resize_objects.c
void		resize_objects(t_win *win, int keysym);

#endif