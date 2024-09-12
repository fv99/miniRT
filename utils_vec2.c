/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:48:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 20:54:12 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// calculates dot product of two vectors
// dot product = two vectors return a single scalar value
// measures how much two vectors are aligned with each other
float	vec_dot(t_float_3 a, t_float_3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// normalizes a vector
// division of its components by its magnitude
t_float_3	vec_normalize(t_float_3 v)
{
	float	length;

	length = vec_length(v);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return (v);
}

// calculates cross product
// takes two vectors, returns a vector that is perpendicular to the first two
t_float_3	vec_cross(t_float_3 v1, t_float_3 v2)
{
	t_float_3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

int	is_zero_vector(t_float_3 vec)
{
	return (vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f);
}

float	vec_cos(t_float_3 a, t_float_3 b)
{
	float	dot;
	float	t;

	dot = vec_dot(a, b);
	t = vec_length(a) * vec_length(b);
	return (dot / t);
}
