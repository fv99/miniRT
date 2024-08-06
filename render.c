/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/06 15:46:19 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int trace_ray(t_ray ray, t_map *map, int *color)
{
    t_trace vars;
    t_sp *sphere = map->spheres;
    float closest_t = INFINITY;
    t_sp *closest_sphere = NULL;

    vars.light_pos = map->light.pos;
    vars.hit = 0;
    while (sphere)
    {
        float t;
        if (sphere_intersect(ray, sphere, &t) && t < closest_t)
        {
            closest_t = t;
            closest_sphere = sphere;
        }
        sphere = sphere->next;
    }
    if (closest_sphere)
    {
        vars.t = closest_t;
        render_sphere(ray, closest_sphere, &vars, color);
    }
    return vars.hit;
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
	if (!hit)
		color = win->map->amb.amb;

    pixel_to_img(win, x, y, color);
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
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    return 0;
}
