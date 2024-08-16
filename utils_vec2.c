/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:48:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/16 16:21:44 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// normalizes a vector
t_float_3 vec_normalize(t_float_3 v)
{
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    // Check for zero-length vector to prevent division by zero
    if (length == 0.0f)
    {
        printf("Warning: Attempted to normalize a zero-length vector.\n");
        return (t_float_3){0.0f, 0.0f, 0.0f};  // Return a default or error value
    }

    v.x /= length;
    v.y /= length;
    v.z /= length;

    return v;
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

int is_zero_vector(t_float_3 vec)
{
    return (vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f);
}
