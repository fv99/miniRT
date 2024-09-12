/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:32:17 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 20:52:28 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float_3	vec_negate(t_float_3 vec)
{
	t_float_3	result;

	result.x = -vec.x;
	result.y = -vec.y;
	result.z = -vec.z;
	return (result);
}

// calculates the magnitude of a vector
float	vec_length(t_float_3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
