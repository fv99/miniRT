/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:24:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 20:00:56 by khlavaty         ###   ########.fr       */
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

// arrow keys and ,,. (z axis) to rotate cylinder
// zxcvbn (z axis) to rotate plane
// WASDQE to move objects
// IKJLUIO to move light
// TGHFYR to move camera
// 456789 to rotate camera
// ESC to exit
// +/- to resize objects

void	handle_keypress_without_angle(int keysym, t_win *win)
{
	if (keysym == KEY_ESC)
		handle_destroy_notify(win);
	else if (keysym == KEY_W || keysym == KEY_S || keysym == KEY_A)
		move_objects(win, keysym);
	else if (keysym == KEY_D || keysym == KEY_Q || keysym == KEY_E)
		move_objects(win, keysym);
	else if (keysym == KEY_I || keysym == KEY_K || keysym == KEY_J)
		move_light(win, keysym);
	else if (keysym == KEY_L || keysym == KEY_U || keysym == KEY_O)
		move_light(win, keysym);
	else if (keysym == KEY_T || keysym == KEY_G || keysym == KEY_F)
		move_camera(win, keysym);
	else if (keysym == KEY_H || keysym == KEY_R || keysym == KEY_Y)
		move_camera(win, keysym);
	else if (keysym == KEY_NUMPAD_PLUS || keysym == KEY_NUMPAD_MINUS)
		resize_objects(win, keysym);
}

void	handle_keypress_with_angle(int keysym, t_win *win)
{
	float	angle;

	angle = RADIANS(1);
	if (keysym == KEY_UP || keysym == KEY_DOWN || keysym == KEY_LEFT)
		rotate_cylinder(win, keysym, angle);
	else if (keysym == KEY_RIGHT || keysym == KEY_DOT || keysym == KEY_COMMA)
		rotate_cylinder(win, keysym, angle);
	else if (keysym == KEY_Z || keysym == KEY_X || keysym == KEY_C)
		rotate_plane(win, keysym, angle);
	else if (keysym == KEY_V || keysym == KEY_B || keysym == KEY_N)
		rotate_plane(win, keysym, angle);
	else if (keysym == KEY_4 || keysym == KEY_5 || keysym == KEY_6)
		rotate_camera(win, keysym, angle);
	else if (keysym == KEY_7 || keysym == KEY_8 || keysym == KEY_9)
		rotate_camera(win, keysym, angle);
}

int	handle_keypress(int keysym, t_win *win)
{
	if (keysym == KEY_UP || keysym == KEY_DOWN || keysym == KEY_LEFT
		|| keysym == KEY_RIGHT || keysym == KEY_DOT || keysym == KEY_COMMA
		|| keysym == KEY_Z || keysym == KEY_X || keysym == KEY_C
		|| keysym == KEY_V || keysym == KEY_B || keysym == KEY_N
		|| keysym == KEY_4 || keysym == KEY_5 || keysym == KEY_6
		|| keysym == KEY_7 || keysym == KEY_8 || keysym == KEY_9)
	{
		handle_keypress_with_angle(keysym, win);
	}
	else
	{
		handle_keypress_without_angle(keysym, win);
	}
	return (0);
}
