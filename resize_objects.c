/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:52:54 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 19:53:14 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resize_objects(t_win *win, int keysym)
{
	t_obj	*obj;
	float	scale_factor;
	t_sp	*sphere;
	t_cy	*cylinder;

	obj = win->map->objects;
	if (keysym == KEY_NUMPAD_PLUS)
		scale_factor = 1.1;
	else
		scale_factor = 0.9;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			sphere = (t_sp *)obj->object;
			sphere->dia *= scale_factor;
		}
		else if (obj->type == CYLINDER)
		{
			cylinder = (t_cy *)obj->object;
			cylinder->dia *= scale_factor;
			cylinder->hth *= scale_factor;
		}
		obj = obj->next;
	}
}
