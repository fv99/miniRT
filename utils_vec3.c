/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:16:36 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/20 18:35:47 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float vec_cos(t_float_3 a, t_float_3 b)
{
    float   dot;
    float   t;

    dot = vec_dot(a, b);
    t = vec_length(a) * vec_length(b);
    return (dot / t);
}
