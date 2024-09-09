/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_illumination.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:34 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/09 12:54:12 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    illuminate(t_map *map, t_trace *closest)
{
    int color;

    color = color_multiply(closest->color, map->amb.lum);
    if (!calculate_shadow(map, closest))
        color = add_colors(color, diffuse(map, closest, map->light.lum));
    closest->color = color;
}

int diffuse(t_map *map, t_trace *closest, float intensity)
{
    t_float_3   light_dir;
    int         ret;
    float       cos_angle;
    float       ratio;
    float       attenuation;

    light_dir = vec_sub(map->light.pos, closest->hit_point);
    attenuation = MIN(1.0, 90.0 / vec_length(light_dir));
    cos_angle = MAX(0.0, vec_cos(closest->normal, light_dir));
    ratio = intensity * cos_angle * attenuation;
    ret = color_multiply(closest->color, ratio);
    return (ret);
}


int calculate_shadow(t_map *map, t_trace *closest)
{
    t_float_3   light_dir;
    t_ray       ray;
    float       dist;

    light_dir = vec_sub(map->light.pos, closest->hit_point);
    dist = vec_length(light_dir) + 0.01;
    ray.orig = vec_add(closest->hit_point, VEC_MINFLOAT);
    ray.dir = vec_normalize(light_dir);
    return (obscured(map, &ray, (float)dist));
}

int obscured(t_map *map, t_ray *ray, float max_dist)
{
    t_obj   *objects;
    float   t;

    t = INFINITY;
    objects = map->objects;

    while (objects != NULL)
    {
        if (intersect(*ray, objects, &t) && t < max_dist)
            return (1);
        objects = objects->next;
    }
    return (0);
}