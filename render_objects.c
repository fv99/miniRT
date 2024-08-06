/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:34 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/06 15:43:25 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render_sphere(t_ray ray, t_sp *sphere, t_trace *vars, int *color)
{
    vars->hit = 1;
    vars->hit_point = vec_add(ray.orig, vec_scale(ray.dir, vars->t));
    vars->normal = vec_normalize(vec_sub(vars->hit_point, sphere->pos));
    vars->light_dir = vec_normalize(vec_sub(vars->light_pos, vars->hit_point));
    vars->intensity = fmax(0, vec_dot(vars->normal, vars->light_dir));
    t_float_3 sphere_color = extract_rgb(sphere->col);
    t_float_3 shaded_color = vec_scale(sphere_color, vars->intensity);
    *color = create_color(shaded_color.x, shaded_color.y, shaded_color.z);
}
