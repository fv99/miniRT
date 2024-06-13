/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:30:59 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 15:42:28 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float_3   vec_sub(t_float_3 a, t_float_3 b)
{
    return (t_float_3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_float_3   vec_add(t_float_3 a, t_float_3 b)
{
    return (t_float_3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_float_3   vec_mul(t_float_3 a, float b)
{
    return (t_float_3){a.x * b, a.y * b, a.z * b};
}

t_float_3   vec_div(t_float_3 a, float b)
{
    return (t_float_3){a.x / b, a.y / b, a.z / b};
}

float   vec_dot(t_float_3 a, t_float_3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}