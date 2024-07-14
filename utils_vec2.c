/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:48:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/07/14 17:58:41 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float_3	vec_normalize(t_float_3 v)
{
    float length = sqrtf(vec_dot(v, v));
    return vec_div(v, length);
}

t_float_3   vec_scale(t_float_3 vec, float scale)
{
    return (t_float_3){vec.x * scale, vec.y * scale, vec.z * scale};
}

