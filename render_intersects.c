/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/10 15:02:11 by fvonsovs         ###   ########.fr       */
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
// calculate quadratic equation coeffivarsents
// calculates vars.disc to see if intersects
// calculates two possible solutions intersection points
// finds the correct intersection point (smallest distance *t)
int sphere_intersect(t_ray ray, t_sp *sphere, float *t)
{
	t_cyl_intersect vars;
	float radius;
	
	radius = sphere->dia / 2.0;
	vars.oc = vec_sub(ray.orig, sphere->pos);
	vars.a = vec_dot(ray.dir, ray.dir);
	vars.b = 2.0 * vec_dot(vars.oc, ray.dir);
	vars.c = vec_dot(vars.oc, vars.oc) - (radius * radius);
	vars.disc = (vars.b * vars.b) - (4 * vars.a * vars.c);
	if (vars.disc < 0)
		return (0);
	vars.t0 = (-vars.b - sqrt(vars.disc)) / (2.0 * vars.a);
	vars.t1 = (-vars.b + sqrt(vars.disc)) / (2.0 * vars.a);
	if (vars.t0 > 1e-6)
		*t = vars.t0;
	else if (vars.t1 > 1e-6)
		*t = vars.t1;
	else
		return (0);
	return (1);
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
		return (*t >= 1e-6);
	}
	return (0);
}
