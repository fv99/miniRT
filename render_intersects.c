/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_intersects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/06 15:37:33 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t1 = (-b - sqrtf(disc)) / (2.0f * a);
	*t = (t0 < t1) ? t0 : t1;
	return (1);
}
