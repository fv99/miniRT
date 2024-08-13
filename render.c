/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:00:19 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/13 14:34:19 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*closest_obj(t_ray ray, t_obj *object, float *closest_t)
{
	t_obj	*ret;
	float	t;

	ret = NULL;
	*closest_t = INFINITY;
	t = 0;
	while (object)
	{
		if (intersect(ray, object, &t) && t < *closest_t)
		{
			*closest_t = t;
			ret = object;
		}
		object = object->next;
	}
	return (ret);
}

int trace_ray(t_ray ray, t_map *map, int *color)
{
    t_trace vars;
	t_obj	*closest;
	float 	closest_t;

    vars.light_pos = map->light.pos;
    vars.hit = 0;

	closest = closest_obj(ray, map->objects, &closest_t);
    if (closest)
    {
		vars.t = closest_t;
		if (closest->type == sphere)
            render_sphere(ray, (t_sp *)closest->object, &vars, color);
		if (closest->type == plane)
			render_plane(ray, (t_pl *)closest->object, &vars, color);

		// if (shadow_ray(vars.hit_point, vars.light_pos, map))
		// {
		// 	*color = *color * SHADOW_INTENSITY;
		// }
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

// int	shadow_ray(t_float_3 hit_point, t_float_3 light_pos, t_map *map)
// {
// 	t_ray shadow_ray;
// 	t_obj *closest;
// 	float closest_t;

// 	shadow_ray.orig = hit_point;
// 	shadow_ray.dir = vec_normalize(vec_sub(light_pos, hit_point));
//     closest = closest_obj(shadow_ray, map->objects, &closest_t);
//     if (closest)
//     {
//         float light_distance = vec_length(vec_sub(light_pos, hit_point));
//         if (closest_t < light_distance)
//             return (1);
//     }
//     return (0);
// }

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
