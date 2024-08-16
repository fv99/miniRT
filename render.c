/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/16 16:33:47 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculates normal depending on type of object a ray hit
t_float_3 calculate_normal(t_obj *object, t_float_3 hit_point)
{
    t_float_3 normal;

    normal = hit_point;

    if (object->type == SPHERE) 
    {
        t_sp *sphere = (t_sp *)object->object;
        normal = vec_normalize(vec_sub(hit_point, sphere->pos));
    } 
    else if (object->type == PLANE) 
    {
        t_pl *plane = (t_pl *)object->object;
        normal = vec_normalize(plane->vec);
    }
	// add cylinders later
    return (normal);
}

t_trace	*closest_obj(t_ray ray, t_trace *closest, t_obj *object)
{
	float	t;
	t_obj	*hit_object = NULL;

	closest->t = INFINITY;
	closest->hit_object.object = NULL;
	t = 0;

	// Debug: Print initial ray info
	// printf("Ray Origin: (%f, %f, %f)\n", ray.orig.x, ray.orig.y, ray.orig.z);
	// printf("Ray Direction: (%f, %f, %f)\n", ray.dir.x, ray.dir.y, ray.dir.z);

	while (object)
	{
		// Debug: Print object type and position
		// if (object->type == SPHERE) {
		// 	t_sp *sphere = (t_sp *)object->object;
		// 	printf("Testing intersection with SPHERE at position: (%f, %f, %f)\n", sphere->pos.x, sphere->pos.y, sphere->pos.z);
		// }
		// else if (object->type == PLANE) {
		// 	t_pl *plane = (t_pl *)object->object;
		// 	printf("Testing intersection with PLANE at position: (%f, %f, %f)\n", plane->pos.x, plane->pos.y, plane->pos.z);
		// }

		if (intersect(ray, object, &t))
		{
			// // Debug: Print intersection distance
			// printf("Intersection found at distance t = %f\n", t);

			if (t < closest->t)
			{
				closest->t = t;
				closest->hit_object = *object;
				closest->ray = ray;
				closest->hit_point = vec_add(ray.orig, vec_scale(ray.dir, closest->t));
				closest->normal = calculate_normal(&closest->hit_object, closest->hit_point);
				hit_object = object;

				// Debug: Print hit point and normal
				// printf("New closest object hit at: (%f, %f, %f)\n", closest->hit_point.x, closest->hit_point.y, closest->hit_point.z);
				// printf("Normal at hit point: (%f, %f, %f)\n", closest->normal.x, closest->normal.y, closest->normal.z);
			}
			// else
			// {
			// 	// Debug: Intersection found but not closer than the current closest
			// 	printf("Intersection at t = %f, but not closer than current closest t = %f\n", t, closest->t);
			// }
		}
		// else
		// {
		// 	// Debug: No intersection found
		// 	printf("No intersection found with this object.\n");
		// }

		object = object->next;
	}
	return (hit_object != NULL) ? closest : NULL;
}


void render_ray(t_win *win, int x, int y)
{
	t_ray		ray;
	t_trace		closest;
	t_float_3	vec;
	int			color;

	color = 0x000000;
	vec = pixels_to_viewport(x, y);
	ray = throw_ray(win->map, vec);

	if (closest_obj(ray, &closest, win->map->objects))
	{
		if (closest.hit_object.type == SPHERE)
			color = 0xFF0000;
		// Set the color based on intersection, lighting, etc. Here, just as a placeholder
		color = 0xFFFFFF; // Example color, you can modify this based on shading logic
	}
	else
	{
		color = 0x000000; // Background color
	}

	pixel_to_img(win, x, y, color);
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
