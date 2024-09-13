/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:50:26 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 18:04:42 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_object(t_obj *obj, float translation, char axis)
{
	if (axis == 'x')
		translate_object_x(obj, translation);
	else if (axis == 'y')
		translate_object_y(obj, translation);
	else if (axis == 'z')
		translate_object_z(obj, translation);
}

void	translate_object_x(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.x += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.x += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.x += translation;
}

void	translate_object_y(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.y += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.y += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.y += translation;
}

void	translate_object_z(t_obj *obj, float translation)
{
	if (obj->type == SPHERE)
		((t_sp *)obj->object)->pos.z += translation;
	else if (obj->type == PLANE)
		((t_pl *)obj->object)->pos.z += translation;
	else if (obj->type == CYLINDER)
		((t_cy *)obj->object)->pos.z += translation;
}

void	translate_objects(t_win *win, float translation, char axis)
{
	t_obj	*obj;

	obj = win->map->objects;
	while (obj)
	{
		translate_object(obj, translation, axis);
		obj = obj->next;
	}
}
