/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/25 15:14:56 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect(t_ray ray, t_obj *obj, float *t)
{
	if (obj->type == SPHERE)
		return(sphere_intersect(ray, obj->object, t));
	if (obj->type == PLANE)
		return(plane_intersect(ray, obj->object, t)); 
	if (obj->type == CYLINDER)
		return(cylinder_intersect(ray, obj->object, t));
	else
		return (0);
}

// calculate vector from ray origin to sphere center
// calculate quadratic equation coefficients
// calculates vars.discriminant to see if intersects
// calculates two possible solutions intersection points
// finds the correct intersection point (smallest distance *t)
int		sphere_intersect(t_ray ray, t_sp *sphere, float *t)
{
    t_float_3 oc = vec_sub(ray.orig, sphere->pos);
    float a = vec_dot(ray.dir, ray.dir);
    float b = 2.0f * vec_dot(oc, ray.dir);
    float c = vec_dot(oc, oc) - (sphere->dia / 2) * (sphere->dia / 2);
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0;
    else
    {
        float sqrt_disc = sqrt(discriminant);
        float t0 = (-b - sqrt_disc) / (2.0f * a);
        float t1 = (-b + sqrt_disc) / (2.0f * a);
        if (t0 > 0)
            *t = t0;
        else if (t1 > 0)
            *t = t1;
        else
            return (0);
        return (1);
    }
}

// calculates dot product between ray direction and plane normal
// if denom is close to 0, it is parallel = no intersection
// if not, calculate vector from ray origin to a point on the plane
// calculate numerator of intersection formula
// calculate intersection distance, if > 0 we hit
int	plane_intersect(t_ray ray, t_pl *plane, float *t)
{
	t_float_3	vec;
	float		denom;
	float		num;

	denom = vec_dot(ray.dir, plane->vec);
	if (fabs(denom) > 1e-6)
	{
		vec = vec_sub(plane->pos, ray.orig);
		num = vec_dot(vec, plane->vec);
		*t = num / denom;
		if (*t >= 0)
			return (1);
	}
	return (0);
}

// calculate vars as described in the struct definition
// checks for intersection with the cylinders side
// if no intersection with the cylindrical side, check the caps
int cylinder_intersect(t_ray ray, t_cy *cylinder, float *t)
{
    t_cyl_intersect vars;
    float sqrt_dist;

    vars.oc = vec_sub(ray.orig, cylinder->pos);
    vars.d = ray.dir;
    vars.a = cylinder->vec;
    vars.d_cross_a = vec_cross(vars.d, vars.a);
    vars.oc_cross_a = vec_cross(vars.oc, vars.a);
    vars.quad.x = vec_dot(vars.d_cross_a, vars.d_cross_a);
    vars.quad.y = 2.0f * vec_dot(vars.d_cross_a, vars.oc_cross_a);
    vars.quad.z = vec_dot(vars.oc_cross_a, vars.oc_cross_a) - (cylinder->dia / 2);
    vars.disc = vars.quad.y * vars.quad.y - 4 * vars.quad.x * vars.quad.z;
    if (vars.disc >= 0)
	{
    	sqrt_dist = sqrt(vars.disc);
		vars.t0 = (-vars.quad.y - sqrt_dist) / (2.0f * vars.quad.x);
		vars.t1 = (-vars.quad.y + sqrt_dist) / (2.0f * vars.quad.x);
		if (is_valid_intersect(&vars, cylinder, ray, t))
			return (1);
	}
    return (0);
}

// determine which intersection point is valid for side of cylinder
// project vector from cylinder base to hit point
// check if we hit a point in heigth of cylinder
int	is_valid_intersect(t_cyl_intersect *vars, t_cy *cylinder, t_ray ray, float *t)
{
	if (vars->t0 > 0 && vars->t1 > 0)
        *t = fmin(vars->t0, vars->t1);
    else if (vars->t0 > 0)
        *t = vars->t0;
    else if (vars->t1 > 0)
        *t = vars->t1;
	else if (vars->t0 < 0 && vars->t1 < 0)
        return (0);
    vars->hit_point = vec_add(ray.orig, vec_mul(ray.dir, *t));
    vars->hit_base = vec_sub(vars->hit_point, cylinder->pos);
    vars->proj_l = vec_dot(vars->hit_base, cylinder->vec);
    if (vars->proj_l < 0 || vars->proj_l > cylinder->hth)
        return (0);
    return (1);
}
