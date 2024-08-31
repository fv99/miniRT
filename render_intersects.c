/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/31 16:18:51 by fvonsovs         ###   ########.fr       */
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
