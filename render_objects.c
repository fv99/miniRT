/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:34 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/12 16:24:26 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render_sphere(t_ray ray, t_sp *sphere, t_trace *vars, int *color)
{
    t_float_3 sphere_color;

    vars->hit = 1;
    vars->hit_point = vec_add(ray.orig, vec_scale(ray.dir, vars->t));
    vars->normal = vec_normalize(vec_sub(vars->hit_point, sphere->pos));
    vars->light_dir = vec_normalize(vec_sub(vars->light_pos, vars->hit_point));
    vars->intensity = fmax(0, vec_dot(vars->normal, vars->light_dir));
    sphere_color = extract_rgb(sphere->col);
    
    // Apply intensity to the sphere color
    sphere_color = vec_scale(sphere_color, vars->intensity);
    *color = create_color(sphere_color.x, sphere_color.y, sphere_color.z);
}
