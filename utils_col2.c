/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_col2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:21:06 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 21:14:32 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_colors(int col1, int col2)
{
	t_int_3	rgb1;
	t_int_3	rgb2;
	t_int_3	ret;

	rgb1 = extract_rgb(col1);
	rgb2 = extract_rgb(col2);
	ret.x = clamp(rgb1.x + rgb2.x, 0, 255);
	ret.y = clamp(rgb1.y + rgb2.y, 0, 255);
	ret.z = clamp(rgb1.z + rgb2.z, 0, 255);
	return (create_color(ret.x, ret.y, ret.z));
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	color_multiply(int color, float ratio)
{
	t_int_3	rgb;
	int		r;
	int		g;
	int		b;

	rgb = extract_rgb(color);
	r = (int)(rgb.x * ratio);
	r = clamp(r, 0, 255);
	g = (int)(rgb.y * ratio);
	g = clamp(g, 0, 255);
	b = (int)(rgb.z * ratio);
	b = clamp(b, 0, 255);
	return (rgb_to_hex(r, g, b));
}
