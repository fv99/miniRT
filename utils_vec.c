/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:30:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/09 12:33:03 by fvonsovs         ###   ########.fr       */
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

// scales a vector by a scalar value
t_float_3 vec_scale(t_float_3 v, float scalar)
{
    return (t_float_3){v.x * scalar, v.y * scalar, v.z * scalar};
}
