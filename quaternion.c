/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:24:54 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 18:43:55 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Function to create a quaternion from an axis and an angle
t_quat	quaternion_from_axis_angle(t_float_3 axis, float angle)
{
	t_quat	q;
	float	half_angle;
	float	s;

	half_angle = angle / 2.0f;
	s = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	return (q);
}

// Function to normalize a quaternion
t_quat	quaternion_normalize(t_quat q)
{
	float	magnitude;

	magnitude = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= magnitude;
	q.x /= magnitude;
	q.y /= magnitude;
	q.z /= magnitude;
	return (q);
}

// Function to multiply two quaternions
t_quat	quaternion_multiply(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (result);
}

// Function to rotate a vector by a quaternion
t_float_3	quaternion_rotate_vector(t_quat q, t_float_3 v)
{
	t_quat	qv;
	t_quat	q_conjugate;
	t_quat	q_result;

	qv.w = 0;
	qv.x = v.x;
	qv.y = v.y;
	qv.z = v.z;
	q_conjugate.w = q.w;
	q_conjugate.x = -q.x;
	q_conjugate.y = -q.y;
	q_conjugate.z = -q.z;
	q_result = quaternion_multiply(quaternion_multiply(q, qv), q_conjugate);
	return ((t_float_3){q_result.x, q_result.y, q_result.z});
}
