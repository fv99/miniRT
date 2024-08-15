/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:30:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/15 14:46:36 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// subtracts two vectors
t_float_3   vec_sub(t_float_3 a, t_float_3 b)
{
    return (t_float_3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// adds two vectors
t_float_3   vec_add(t_float_3 a, t_float_3 b)
{
    return (t_float_3){a.x + b.x, a.y + b.y, a.z + b.z};
}

// multiples a vector by a scalar
t_float_3   vec_mul(t_float_3 a, float b)
{
    return (t_float_3){a.x * b, a.y * b, a.z * b};
}

// divides a vector by a scalar
t_float_3   vec_div(t_float_3 a, float b)
{
    return (t_float_3){a.x / b, a.y / b, a.z / b};
}

// computes dot product of two vectors
// dot product = two vectors return a single cscalar value
// measures how much two vectors are alignedwith each other
float       vec_dot(t_float_3 a, t_float_3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}