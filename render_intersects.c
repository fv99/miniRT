/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/13 14:34:02 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		intersect(t_ray ray, t_obj *obj, float *t)
{
	if (obj->type == sphere)
		return(sphere_intersect(ray, obj->object, t));
	if (obj->type == plane)
		return(plane_intersect(ray, obj->object, t)); 
	// if (obj->type == cylinder)
		// return
	else
		return (0);
}

// calculate vector from ray origin to sphere center
// calculate quadratic equation coefficients
// calculates discriminant to see if intersects
// calculates two possible solutions intersection points
// finds the correct intersection point (smallest distance *t)
int		sphere_intersect(t_ray ray, t_sp *sphere, float *t)
{
	t_float_3	oc;
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t0;
	float	t1;

	oc = vec_sub(ray.orig, sphere->pos);
	a = vec_dot(ray.dir, ray.dir);
	b = 2.0f * vec_dot(oc, ray.dir);
	c = vec_dot(oc, oc) - (sphere->dia / 2) * (sphere->dia / 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrtf(disc)) / (2.0f * a);
	t1 = (-b + sqrtf(disc)) / (2.0f * a);
	if (t0 > 0 && t1 > 0)
		*t = (t0 < t1) ? t0 : t1;
	else if (t1 > 0)
		*t = t1;
	else if (t0 > 0)
		*t = t0;
	else
		return (0); // both t0 and t1 are negative
	return (1);
}

// calculates dot product between ray direction and plane normal
// if denom is close to 0, it is parallel = no intersection
// if not, calculate vector from ray origin to a point on the plane
// calculate numerator of intersection formula
// calculate intersection distance, if > 0 we hit
int		plane_intersect(t_ray ray, t_pl *plane, float *t)
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