/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 20:23:33 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int render(t_win *win)
{
    t_ray ray;
    float t;
    float px;
    float py;
    int x;
    int y;
    int hit;
    int color;

    ray.orig = win->map->cam.pos;
    win->scene.scale = tan(win->map->cam.fov / 2 * M_PI / 180);
    win->scene.aspect_ratio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;

    for (y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            px = (2 * (x + 0.5) / (float)WINDOW_WIDTH - 1) * win->scene.scale * win->scene.aspect_ratio;
            py = (1 - 2 * (y + 0.5) / (float)WINDOW_HEIGHT) * win->scene.scale;
            ray.dir = vec_normalize(vec_add(win->map->cam.vec, (t_float_3){px, py, -1}));

            t_sp *sphere = win->map->spheres;
            hit = 0;

            while (sphere)
            {
                if (sphere_intersect(ray, sphere, &t))
                {
                    hit = 1;
                    color = sphere->col;
                    break;
                }
                sphere = sphere->next;
            }

            mlx_pixel_put(win->mlx, win->win, x, y, hit ? color : win->map->amb.col);
        }
    }
    return 0;
}

int		sphere_intersect(t_ray ray, t_sp *sphere, float *t)
{
	t_float_3	oc;
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t0;
	float	t1;

	oc = vec_sub(ray.orig, sphere->pos);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0f * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - (sphere->dia / 2) * (sphere->dia / 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrtf(disc)) / (2.0f * a);
	t1 = (-b - sqrtf(disc)) / (2.0f * a);
	*t = (t0 < t1) ? t0 : t1;
	return (1);
}

t_float_3 vec_normalize(t_float_3 v)
{
    float length = sqrtf(vec_dot(v, v));
    return vec_div(v, length);
}