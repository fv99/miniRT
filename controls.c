/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:24:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/14 16:49:44 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_destroy_notify(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	print_controls(t_win *win)
{
	mlx_string_put(win->mlx, win->win, 10, 10, 0xFFFFFF, "miniRT");
	return (0);
}

// quaternion rotation

// Function to create a quaternion from an axis and an angle
t_quaternion quaternion_from_axis_angle(t_float_3 axis, float angle)
{
	t_quaternion q;
	float half_angle = angle / 2.0f;
	float s = sin(half_angle);

	q.w = cos(half_angle);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;

	return (q);
}

// Function to normalize a quaternion
t_quaternion quaternion_normalize(t_quaternion q)
{
	float magnitude = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= magnitude;
	q.x /= magnitude;
	q.y /= magnitude;
	q.z /= magnitude;

	return (q);
}

// Function to multiply two quaternions
t_quaternion quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

	return (result);
}

// Function to rotate a vector by a quaternion
t_float_3 quaternion_rotate_vector(t_quaternion q, t_float_3 v)
{
	t_quaternion qv = {0, v.x, v.y, v.z};
	t_quaternion q_conjugate = {q.w, -q.x, -q.y, -q.z};

	t_quaternion q_result = quaternion_multiply(quaternion_multiply(q, qv), q_conjugate);

	return (t_float_3){q_result.x, q_result.y, q_result.z};
}

void perform_cylinder_rotation(t_cy *cylinder, t_quaternion q)
{
    // Normalizing the quaternion to avoid any distortion due to numerical errors
	// maybe delete this
    q = quaternion_normalize(q);

    // Calculating the center of the cylinder
    t_float_3 center;
    center.x = cylinder->pos.x + (cylinder->vec.x * (cylinder->hth / 2.0f));
    center.y = cylinder->pos.y + (cylinder->vec.y * (cylinder->hth / 2.0f));
    center.z = cylinder->pos.z + (cylinder->vec.z * (cylinder->hth / 2.0f));

    // Rotating the direction vector using the quaternion
    t_float_3 rotated_vec = quaternion_rotate_vector(q, cylinder->vec);

    // Recomputing the position to ensure the center remains stable
    t_float_3 new_pos;
    new_pos.x = center.x - (rotated_vec.x * (cylinder->hth / 2.0f));
    new_pos.y = center.y - (rotated_vec.y * (cylinder->hth / 2.0f));
    new_pos.z = center.z - (rotated_vec.z * (cylinder->hth / 2.0f));

    // Updating the cylinder's vector and position
    cylinder->vec = rotated_vec;
    cylinder->pos = new_pos;
}

void perform_plane_rotation(t_pl *plane, t_quaternion q)
{
    // Rotate the plane's normal vector
    t_float_3 rotated_vec = quaternion_rotate_vector(q, plane->vec);

    // Update the plane's normal vector
    plane->vec = rotated_vec;
}

void rotate_object(t_obj *obj, t_quaternion q)
{
	if (obj->type == CYLINDER)
	{
		t_cy *cylinder = (t_cy *)obj->object;
		perform_cylinder_rotation(cylinder, q);
	}
	else if (obj->type == PLANE)
	{
		t_pl *plane = (t_pl *)obj->object;
		perform_plane_rotation(plane, q);
	}
}

void translate_object(t_obj *obj, float translation, char axis)
{
    if (axis == 'x')
        translate_object_x(obj, translation);
    else if (axis == 'y')
        translate_object_y(obj, translation);
    else if (axis == 'z')
        translate_object_z(obj, translation);
}

void translate_object_x(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.x += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.x += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.x += translation;
}

void translate_object_y(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.y += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.y += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.y += translation;
}

void translate_object_z(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.z += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.z += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.z += translation;
}

void translate_objects(t_win *win, float translation, char axis)
{
    t_obj *obj = win->map->objects;
    while (obj)
    {
        translate_object(obj, translation, axis);
        obj = obj->next;
    }
}

void perform_camera_rotation(t_win *win, t_quaternion q)
{
    // Normalizing the quaternion to avoid any distortion due to numerical errors
	// might not be needed
    q = quaternion_normalize(q);

    // Rotate the camera vector
    win->map->cam.vec = quaternion_rotate_vector(q, win->map->cam.vec);

    // Recalculate the right and up vectors
    t_float_3 vec_right = vec_normalize(vec_cross(win->map->cam.vec, UP_VECTOR));
    t_float_3 vec_up = vec_normalize(vec_cross(vec_right, win->map->cam.vec));

    // Update the camera's right and up vectors in the map
    win->map->vec_right = vec_right;
    win->map->vec_up = vec_up;
}

void rotate_cylinder(t_win *win, int keysym, float angle)
{
    t_quaternion q;
    t_float_3 axis = {0.0, 0.0, 0.0};

    if (keysym == KEY_UP)
        axis = (t_float_3){1.0, 0.0, 0.0}; // Rotate around x-axis
    else if (keysym == KEY_DOWN)
        axis = (t_float_3){-1.0, 0.0, 0.0}; // Rotate around x-axis in the opposite direction
    else if (keysym == KEY_LEFT)
        axis = (t_float_3){0.0, 1.0, 0.0}; // Rotate around y-axis
    else if (keysym == KEY_RIGHT)
        axis = (t_float_3){0.0, -1.0, 0.0}; // Rotate around y-axis in the opposite direction
    else if (keysym == KEY_DOT)
        axis = (t_float_3){0.0, 0.0, 1.0}; // Rotate around z-axis
    else if (keysym == KEY_COMMA)
        axis = (t_float_3){0.0, 0.0, -1.0}; // Rotate around z-axis in the opposite direction

    q = quaternion_from_axis_angle(axis, angle);

    t_obj *obj = win->map->objects;
    while (obj)
    {
        if (obj->type == CYLINDER)
            rotate_object(obj, q);
        obj = obj->next;
    }
}

void rotate_plane(t_win *win, int keysym, float angle)
{
    t_quaternion q;
    t_float_3 axis = {0.0, 0.0, 0.0};

    if (keysym == KEY_Z)
        axis = (t_float_3){1.0, 0.0, 0.0}; // Rotate around x-axis
    else if (keysym == KEY_X)
        axis = (t_float_3){-1.0, 0.0, 0.0}; // Rotate around x-axis in the opposite direction
    else if (keysym == KEY_C)
        axis = (t_float_3){0.0, 1.0, 0.0}; // Rotate around y-axis
    else if (keysym == KEY_V)
        axis = (t_float_3){0.0, -1.0, 0.0}; // Rotate around y-axis in the opposite direction
    else if (keysym == KEY_B)
        axis = (t_float_3){0.0, 0.0, 1.0}; // Rotate around z-axis
    else if (keysym == KEY_N)
        axis = (t_float_3){0.0, 0.0, -1.0}; // Rotate around z-axis in the opposite direction

    q = quaternion_from_axis_angle(axis, angle);

    t_obj *obj = win->map->objects;
    while (obj)
    {
        if (obj->type == PLANE)
            rotate_object(obj, q);
        obj = obj->next;
    }
}

void move_objects(t_win *win, int keysym)
{
    if (keysym == KEY_W)
        translate_objects(win, 0.1, 'y');
    else if (keysym == KEY_S)
        translate_objects(win, -0.1, 'y');
    else if (keysym == KEY_A)
        translate_objects(win, -0.1, 'x');
    else if (keysym == KEY_D)
        translate_objects(win, 0.1, 'x');
    else if (keysym == KEY_Q)
        translate_objects(win, -0.1, 'z');
    else if (keysym == KEY_E)
        translate_objects(win, 0.1, 'z');
}

void move_light(t_win *win, int keysym)
{
    if (keysym == KEY_I)
        win->map->light.pos.y += 0.1;
    else if (keysym == KEY_K)
        win->map->light.pos.y -= 0.1;
    else if (keysym == KEY_J)
        win->map->light.pos.x -= 0.1;
    else if (keysym == KEY_L)
        win->map->light.pos.x += 0.1;
    else if (keysym == KEY_U)
        win->map->light.pos.z -= 0.1;
    else if (keysym == KEY_O)
        win->map->light.pos.z += 0.1;
}

void move_camera(t_win *win, int keysym)
{
    if (keysym == KEY_T)
        win->map->cam.pos.y -= 0.1;
    else if (keysym == KEY_G)
        win->map->cam.pos.y += 0.1;
    else if (keysym == KEY_F)
        win->map->cam.pos.x -= 0.1;
    else if (keysym == KEY_H)
        win->map->cam.pos.x += 0.1;
    else if (keysym == KEY_R)
        win->map->cam.pos.z -= 0.1;
    else if (keysym == KEY_Y)
        win->map->cam.pos.z += 0.1;
}

void rotate_camera(t_win *win, int keysym, float angle)
{
    t_float_3 axis = {0.0, 0.0, 0.0};
    t_quaternion q;

    if (keysym == KEY_4)
        axis = (t_float_3){1.0, 0.0, 0.0}; // Rotate around x-axis
    else if (keysym == KEY_5)
        axis = (t_float_3){-1.0, 0.0, 0.0}; // Rotate around x-axis in the opposite direction
    else if (keysym == KEY_6)
        axis = (t_float_3){0.0, 1.0, 0.0}; // Rotate around y-axis
    else if (keysym == KEY_7)
        axis = (t_float_3){0.0, -1.0, 0.0}; // Rotate around y-axis in the opposite direction
    else if (keysym == KEY_8)
        axis = (t_float_3){0.0, 0.0, 1.0}; // Rotate around z-axis
    else if (keysym == KEY_9)
        axis = (t_float_3){0.0, 0.0, -1.0}; // Rotate around z-axis in the opposite direction

    q = quaternion_from_axis_angle(axis, angle);
    perform_camera_rotation(win, q);
}

// arrow keys and ,,. (z axis) to rotate cylinder
// zxcvbn (z axis) to rotate plane
// WASDQE to move objects
// IKJLUIO to move light
// TGHFYR to move camera
// 456789 to rotate camera
// ESC to exit
// rotation section
int handle_keypress(int keysym, t_win *win)
{
    float angle = RADIANS(1); // 1 degree rotation

    if (keysym == KEY_ESC)
        handle_destroy_notify(win);
    else if (keysym == KEY_UP || keysym == KEY_DOWN || keysym == KEY_LEFT || keysym == KEY_RIGHT || keysym == KEY_DOT || keysym == KEY_COMMA)
        rotate_cylinder(win, keysym, angle);
    else if (keysym == KEY_Z || keysym == KEY_X || keysym == KEY_C || keysym == KEY_V || keysym == KEY_B || keysym == KEY_N)
        rotate_plane(win, keysym, angle);
    else if (keysym == KEY_W || keysym == KEY_S || keysym == KEY_A || keysym == KEY_D || keysym == KEY_Q || keysym == KEY_E)
        move_objects(win, keysym);
    else if (keysym == KEY_I || keysym == KEY_K || keysym == KEY_J || keysym == KEY_L || keysym == KEY_U || keysym == KEY_O)
        move_light(win, keysym);
    else if (keysym == KEY_T || keysym == KEY_G || keysym == KEY_F || keysym == KEY_H || keysym == KEY_R || keysym == KEY_Y)
        move_camera(win, keysym);
    else if (keysym == KEY_4 || keysym == KEY_5 || keysym == KEY_6 || keysym == KEY_7 || keysym == KEY_8 || keysym == KEY_9)
        rotate_camera(win, keysym, angle);

    return (0);
}
