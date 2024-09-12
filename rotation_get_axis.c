/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_get_axis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:06:45 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 19:11:30 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float_3	get_rot_axis_plane(int keysym)
{
	t_float_3	axis;

	axis.x = 0.0;
	axis.y = 0.0;
	axis.z = 0.0;
	if (keysym == KEY_Z)
		axis = (t_float_3){1.0, 0.0, 0.0};
	else if (keysym == KEY_X)
		axis = (t_float_3){-1.0, 0.0, 0.0};
	else if (keysym == KEY_C)
		axis = (t_float_3){0.0, 1.0, 0.0};
	else if (keysym == KEY_V)
		axis = (t_float_3){0.0, -1.0, 0.0};
	else if (keysym == KEY_B)
		axis = (t_float_3){0.0, 0.0, 1.0};
	else if (keysym == KEY_N)
		axis = (t_float_3){0.0, 0.0, -1.0};
	return (axis);
}

t_float_3	get_rot_axis_cylinder(int keysym)
{
	t_float_3	axis;

	axis.x = 0.0;
	axis.y = 0.0;
	axis.z = 0.0;
	if (keysym == KEY_UP)
		axis = (t_float_3){1.0, 0.0, 0.0};
	else if (keysym == KEY_DOWN)
		axis = (t_float_3){-1.0, 0.0, 0.0};
	else if (keysym == KEY_LEFT)
		axis = (t_float_3){0.0, 1.0, 0.0};
	else if (keysym == KEY_RIGHT)
		axis = (t_float_3){0.0, -1.0, 0.0};
	else if (keysym == KEY_DOT)
		axis = (t_float_3){0.0, 0.0, 1.0};
	else if (keysym == KEY_COMMA)
		axis = (t_float_3){0.0, 0.0, -1.0};
	return (axis);
}

t_float_3	get_rot_axis_camera(int keysym)
{
	t_float_3	axis;

	axis.x = 0.0;
	axis.y = 0.0;
	axis.z = 0.0;
	if (keysym == KEY_4)
		axis = (t_float_3){1.0, 0.0, 0.0};
	else if (keysym == KEY_5)
		axis = (t_float_3){-1.0, 0.0, 0.0};
	else if (keysym == KEY_6)
		axis = (t_float_3){0.0, 1.0, 0.0};
	else if (keysym == KEY_7)
		axis = (t_float_3){0.0, -1.0, 0.0};
	else if (keysym == KEY_8)
		axis = (t_float_3){0.0, 0.0, 1.0};
	else if (keysym == KEY_9)
		axis = (t_float_3){0.0, 0.0, -1.0};
	return (axis);
}
