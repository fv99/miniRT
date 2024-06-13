/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 20:56:37 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int trace_ray(t_ray ray, t_map *map, int *color)
{
    t_sp *sphere = map->spheres;
    float t;
    int hit = 0;
    t_float_3 hit_point, normal, light_dir;
    float intensity;
    t_float_3 light_pos = map->light.pos;

    while (sphere)
    {
        if (sphere_intersect(ray, sphere, &t))
        {
            hit = 1;
            hit_point = vec_add(ray.orig, vec_scale(ray.dir, t));
            normal = vec_normalize(vec_sub(hit_point, sphere->pos));
            light_dir = vec_normalize(vec_sub(light_pos, hit_point));
            intensity = fmax(0, vec_dot(normal, light_dir));
            t_float_3 sphere_color = {((sphere->col >> 16) & 0xFF) / 255.0f,		// change this later
                                      ((sphere->col >> 8) & 0xFF) / 255.0f,
                                      (sphere->col & 0xFF) / 255.0f};
            t_float_3 shaded_color = vec_scale(sphere_color, intensity);
            *color = create_color(shaded_color.x, shaded_color.y, shaded_color.z);
            break;
        }
        sphere = sphere->next;
    }
    return (hit);
}

void	render_ray(t_win *win, int x, int y)
{
	t_ray	ray;
	float	px;
	float	py;
	int		color;
	int		hit;

	ray.orig = win->map->cam.pos;
    px = (2 * (x + 0.5) / (float)WINDOW_WIDTH - 1) * win->scene.scale * win->scene.aspect_ratio;
    py = (1 - 2 * (y + 0.5) / (float)WINDOW_HEIGHT) * win->scene.scale;
    ray.dir = vec_normalize(vec_add(win->map->cam.vec, (t_float_3){px, py, -1}));

	hit = trace_ray(ray, win->map, &color);

	mlx_pixel_put(win->mlx, win->win, x, y, hit ? color : win->map->amb.col);
}

int render(t_win *win)
{
    int x;
    int y;

	x = 0;
	y = 0;
	win->scene.scale = tan(win->map->cam.fov / 2 * M_PI / 180);
	win->scene.aspect_ratio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
	
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
