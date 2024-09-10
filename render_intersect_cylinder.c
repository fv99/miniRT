/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersect_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:17:51 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/10 13:54:57 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculate vars as described in the struct definition
// checks for intersection with the cylinders side
// if no intersection with the cylindrical side, check the caps
int cylinder_intersect(t_ray ray, t_cy *cylinder, float *t)
{
    t_cyl_intersect vars;

    vars.hit_side = 0;
    vars.hit_cap = 0;
	vars.dia = cylinder->dia;
    vars.oc = vec_sub(ray.orig, cylinder->pos);
    vars.cyl_vec = vec_normalize(cylinder->vec);
    vars.d_cross_a = vec_cross(ray.dir, vars.cyl_vec);
    vars.oc_cross_a = vec_cross(vars.oc, vars.cyl_vec);
    vars.a = vec_dot(vars.d_cross_a, vars.d_cross_a);
    vars.b = 2.0f * vec_dot(vars.d_cross_a, vars.oc_cross_a);
    vars.c = vec_dot(vars.oc_cross_a, vars.oc_cross_a) - (cylinder->dia / 2) * (cylinder->dia / 2);
    vars.disc = vars.b * vars.b - 4 * vars.a * vars.c;
    vars.hit_side = hit_cyl_side(ray, cylinder, &vars, t);
    vars.hit_cap = hit_cyl_cap(ray, cylinder, &vars, t);

    return (vars.hit_side || vars.hit_cap);
}

int hit_cyl_side(t_ray ray, t_cy *cylinder, t_cyl_intersect *vars, float *t)
{
    if (vars->disc >= 0)
    {
        vars->t0 = (-vars->b - sqrt(vars->disc)) / (2.0f * vars->a);
        vars->t1 = (-vars->b + sqrt(vars->disc)) / (2.0f * vars->a);
        
        if (vars->t0 > vars->t1)
            vars->t0 = vars->t1;
        if (vars->t0 >= 1e-6)
        {
            vars->hit_point = vec_add(ray.orig, vec_mul(ray.dir, vars->t0));
            vars->hit_base = vec_sub(vars->hit_point, cylinder->pos);
            vars->proj_l = vec_dot(vars->hit_base, vars->cyl_vec);
            if (vars->proj_l >= 0 && vars->proj_l <= cylinder->hth)
            {
                *t = vars->t0;
                return (1);
            }
        }
    }
    return (0);
}


int hit_cyl_cap(t_ray ray, t_cy *cylinder, t_cyl_intersect *vars, float *t)
{
    t_float_3 top_center;
    float t_cap;

    top_center = vec_add(cylinder->pos, vec_mul(vars->cyl_vec, cylinder->hth));
    if (intersect_disk(ray, top_center, vars, &t_cap))
    {
        if (!vars->hit_side || t_cap < *t - 1e-6)
        {
            *t = t_cap;
            return (1);
        }
    }
    if (intersect_disk(ray, cylinder->pos, vars, &t_cap))
    {
        if (!vars->hit_side || t_cap < *t - 1e-6)
        {
            *t = t_cap;
            return (1);
        }
    }
    return (0);
}


// calculate denominator for intersection with the plane of the disk
// calculate the intersection point with the plane
// if the intersection is in the point of the ray, calculate the point
// check if we are within the diameter of the disk
int intersect_disk(t_ray ray, t_float_3 disk_center, t_cyl_intersect *vars, float *t)
{
    t_float_3   vec;
    t_float_3   hit_point;
    float       denom;
    float       t_temp;

    denom = vec_dot(ray.dir, vars->cyl_vec);
    if (fabs(denom) > 1e-4)
    {
        vec = vec_sub(disk_center, ray.orig);
        t_temp = vec_dot(vec, vars->cyl_vec) / denom;
        if (t_temp >= 1e-6)
        {
            hit_point = vec_add(ray.orig, vec_mul(ray.dir, t_temp));
            if (vec_length(vec_sub(hit_point, disk_center)) <= (vars->dia / 2.0f))
            {
                *t = t_temp;
                return (1);
            }
        }
    }
    return (0);
}
