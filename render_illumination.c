/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_illumination.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:34 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/14 15:18:38 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	illuminate(t_map *map, t_trace *closest)
{
	int	color;

	color = color_multiply(closest->color, map->amb.lum);
	if (!calculate_shadow(map, closest))
		color = add_colors(color, diffuse(map, closest, map->light.lum));
	closest->color = color;
}

int	diffuse(t_map *map, t_trace *closest, float intensity)
{
	t_float_3	light_dir;
	int			ret;
	float		cos_angle;
	float		ratio;
	float		attenuation;

	light_dir = vec_sub(map->light.pos, closest->hit_point);
	attenuation = (90.0 / vec_length(light_dir));
	if (attenuation > 1.0f)
		attenuation = 1.0f;
	cos_angle = vec_cos(closest->normal, light_dir);
	if (cos_angle < 0.0f)
		cos_angle = 0.0f;
	ratio = intensity * cos_angle * attenuation;
	ret = color_multiply(closest->color, ratio);
	return (ret);
}

int	calculate_shadow(t_map *map, t_trace *closest)
{
	t_float_3	light_dir;
	t_ray		ray;
	float		dist;

	light_dir = vec_sub(map->light.pos, closest->hit_point);
	dist = vec_length(light_dir);
	ray.orig = vec_add(closest->hit_point, vec_mul(closest->normal, 1e-4));
	ray.dir = vec_normalize(light_dir);
	return (obscured(map, &ray, closest->hit_object.object, dist));
}

int	obscured(t_map *map, t_ray *ray, t_obj *closest, float max_dist)
{
	t_obj	*objects;
	float	t;

	t = INFINITY;
	objects = map->objects;
	while (objects != NULL)
	{
		if (objects->id == closest->id)
			objects = objects->next;
		if (intersect(*ray, objects, &t) && t < max_dist)
			return (1);
		objects = objects->next;
	}
	return (0);
}
