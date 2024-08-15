/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:48:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/15 14:46:13 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// normalizes a vector
t_float_3	vec_normalize(t_float_3 v)
{
    float length = sqrtf(vec_dot(v, v));
    return vec_div(v, length);
}

// scales a vector by a scalar
t_float_3   vec_scale(t_float_3 vec, float scale)
{
    return (t_float_3){vec.x * scale, vec.y * scale, vec.z * scale};
}

// calculates the magnitude of a vector
float       vec_length(t_float_3 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// calculates cross product
// takes two vectors, returns a vector that is perpendicular to the first two
t_float_3 vec_cross(t_float_3 v1, t_float_3 v2)
{
    t_float_3 res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return res;
}

