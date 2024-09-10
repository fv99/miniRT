/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:40:21 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/10 16:13:24 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float_3 sphere_normal(t_trace *inter)
{
    t_float_3 normal;
    t_sp *sphere;

    sphere = (t_sp *)inter->hit_object.object;
    normal = vec_sub(inter->hit_point, sphere->pos);
    return (normal);
}

t_float_3 cylinder_normal(t_trace *inter, t_ray ray)
{
    t_float_3 point;
    t_float_3 normal;
    t_cy *cylinder;

    cylinder = (t_cy *)inter->hit_object.object;
    point = vec_add(ray.orig, vec_mul(ray.dir, inter->t));
    normal = vec_sub(point, cylinder->pos);
    return (normal);
}

t_float_3 plane_normal(t_trace *inter, t_ray ray)
{
    t_float_3 normal;
    t_pl *plane;

    plane = (t_pl *)inter->hit_object.object;
    normal = plane->vec;

    if (vec_dot(ray.dir, normal) > 0)
    {
        normal = vec_negate(normal);
    }

    return vec_normalize(normal);
}

t_float_3 shape_normal(t_trace *inter, t_ray ray)
{
    if (inter->hit_object.type == PLANE)
        return plane_normal(inter, ray);
    else if (inter->hit_object.type == SPHERE)
        return sphere_normal(inter);
    else
        return cylinder_normal(inter, ray);
}

