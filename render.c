/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/22 20:53:48 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculates normal depending on type of object a ray hit
t_float_3 calculate_normal(t_obj *object, t_float_3 hit_point)
{
    t_float_3 normal;
	t_sp *sphere;
	t_pl *plane;
	//t_cy *cylinder;

	sphere = NULL;
	plane = NULL;
    normal = hit_point;

    if (object->type == SPHERE) 
    {
        sphere = (t_sp *)object->object;
        normal = vec_sub(hit_point, sphere->pos);
    } 
    else if (object->type == PLANE) 
    {
        plane = (t_pl *)object->object;
        normal = plane->vec;
    }
	// add cylinders here later
    return (normal);
}

t_trace	*closest_obj(t_ray ray, t_trace *closest, t_obj *object)
{
	float	t;
	t_obj	*hit_object = NULL;

	closest->t = INFINITY;
	closest->hit_object.object = NULL;
	t = 0;

	while (object)
	{
		if (intersect(ray, object, &t))
		{
			if (t < closest->t)
			{
				closest->t = t;
				closest->hit_object = *object;
				closest->ray = ray;
				closest->hit_point = vec_add(ray.orig, vec_mul(ray.dir, closest->t));
				closest->normal = calculate_normal(&closest->hit_object, closest->hit_point);
				closest->color = closest->hit_object.color;
				hit_object = object;
			}
		}
		object = object->next;
	}
	return (hit_object != NULL) ? closest : NULL;
}


void render_ray(t_win *win, int x, int y)
{
	t_ray		ray;
	t_trace		closest;
	t_float_3	vec;

	vec = pixels_to_viewport(x, y);
	ray = throw_ray(win->map, vec);
	if (closest_obj(ray, &closest, win->map->objects))
		illuminate(win->map, &closest);

	pixel_to_img(win, x, y, closest.color);
	closest.color = 0x000000;
}

int render(t_win *win)
{
    int x;
    int y;

	x = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			render_ray(win, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    return (0);
}
