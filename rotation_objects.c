/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:44:28 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 19:09:52 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	perform_cylinder_rotation(t_cy *cylinder, t_quat q)
{
	t_float_3	center;
	t_float_3	rotated_vec;
	t_float_3	new_pos;

	q = quaternion_normalize(q);
	center.x = cylinder->pos.x + (cylinder->vec.x * (cylinder->hth / 2.0f));
	center.y = cylinder->pos.y + (cylinder->vec.y * (cylinder->hth / 2.0f));
	center.z = cylinder->pos.z + (cylinder->vec.z * (cylinder->hth / 2.0f));
	rotated_vec = quaternion_rotate_vector(q, cylinder->vec);
	new_pos.x = center.x - (rotated_vec.x * (cylinder->hth / 2.0f));
	new_pos.y = center.y - (rotated_vec.y * (cylinder->hth / 2.0f));
	new_pos.z = center.z - (rotated_vec.z * (cylinder->hth / 2.0f));
	cylinder->vec = rotated_vec;
	cylinder->pos = new_pos;
}

void	perform_plane_rotation(t_pl *plane, t_quat q)
{
	t_float_3	rotated_vec;

	rotated_vec = quaternion_rotate_vector(q, plane->vec);
	plane->vec = rotated_vec;
}

void	rotate_object(t_obj *obj, t_quat q)
{
	t_cy	*cylinder;
	t_pl	*plane;

	if (obj->type == CYLINDER)
	{
		cylinder = (t_cy *)obj->object;
		perform_cylinder_rotation(cylinder, q);
	}
	else if (obj->type == PLANE)
	{
		plane = (t_pl *)obj->object;
		perform_plane_rotation(plane, q);
	}
}

void	rotate_cylinder(t_win *win, int keysym, float angle)
{
	t_quat		q;
	t_float_3	axis;
	t_obj		*obj;

	axis = get_rot_axis_cylinder(keysym);
	q = quaternion_from_axis_angle(axis, angle);
	obj = win->map->objects;
	while (obj)
	{
		if (obj->type == CYLINDER)
			rotate_object(obj, q);
		obj = obj->next;
	}
}

void	rotate_plane(t_win *win, int keysym, float angle)
{
	t_quat		q;
	t_float_3	axis;
	t_obj		*obj;

	axis = get_rot_axis_plane(keysym);
	q = quaternion_from_axis_angle(axis, angle);
	obj = win->map->objects;
	while (obj)
	{
		if (obj->type == PLANE)
			rotate_object(obj, q);
		obj = obj->next;
	}
}
