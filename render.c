/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 14:21:48 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_trace	*closest_obj(t_ray ray, t_trace *closest, t_obj *object)
{
	float	t;
	t_obj	*hit_object = NULL;

	closest->t = INFINITY;
	closest->hit_object.object = NULL;
	closest->color = 0x000000;
	t = INFINITY;
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
				closest->normal = shape_normal(closest, ray);
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
}

void *threaded_render(void *arg)
{
    t_thread *data = (t_thread *)arg;
    int x, y;

    y = data->start_y;
    while (y < data->end_y)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            render_ray(data->win, x, y);
            x++;
        }
        y++;
    }
    return NULL;

}

int render(t_win *win)
{
    pthread_t threads[win->num_cores];
    t_thread thread_data[win->num_cores];
    int rows;
    int i;

	i = 0;
	rows = WINDOW_HEIGHT / win->num_cores;
    while (i < win->num_cores)
    {
        thread_data[i].win = win;
        thread_data[i].start_y = i * rows;
        thread_data[i].end_y = (i == win->num_cores - 1) ? WINDOW_HEIGHT : (i + 1) * rows;
        pthread_create(&threads[i], NULL, threaded_render, &thread_data[i]);
		i++;
    }
	i = 0;
    while (i < win->num_cores)
    {
        pthread_join(threads[i], NULL);
		i++;
    }

    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    return (0);
}
