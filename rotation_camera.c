/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:16:20 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/14 15:10:30 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	perform_camera_rotation(t_win *win, t_quat q)
{
	t_float_3	vec_right;
	t_float_3	vec_up;

	q = quaternion_normalize(q);
	win->map->cam.vec = quaternion_rotate_vector(q, win->map->cam.vec);
	vec_right = vec_normalize(vec_cross(win->map->cam.vec, \
	(t_float_3){0.0, -1.0, 0.0}));
	vec_up = vec_normalize(vec_cross(vec_right, win->map->cam.vec));
	win->map->vec_right = vec_right;
	win->map->vec_up = vec_up;
}

void	rotate_camera(t_win *win, int keysym, float angle)
{
	t_float_3	axis;
	t_quat		q;

	axis = get_rot_axis_camera(keysym);
	q = quaternion_from_axis_angle(axis, angle);
	perform_camera_rotation(win, q);
}
