/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_col2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:21:06 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/20 18:55:09 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int add_colors(int col1, int col2)
{
    t_float_3   rgb1;
    t_float_3   rgb2;
    t_float_3   ret;

    rgb1 = extract_rgb(col1);
    rgb2 = extract_rgb(col2);
    ret.x = clamp(rgb1.x + rgb2.x, 0, 255);
    ret.y = clamp(rgb1.y + rgb2.y, 0, 255);
    ret.z = clamp(rgb1.z + rgb2.z, 0, 255);
    return(create_color(ret.x, ret.y, ret.z));
}


int clamp(int value, int min, int max)
{
    if (value < min)
        return (min);
    if (value > max)
        return (max);
    return (value);
}

int color_multiply(int color, float ratio)
{
    t_float_3 rgb = extract_rgb(color);
    int r = clamp((int)(rgb.x * ratio * 255), 0, 255);
    int g = clamp((int)(rgb.y * ratio * 255), 0, 255);
    int b = clamp((int)(rgb.z * ratio * 255), 0, 255);
    return rgb_to_hex(r, g, b);
}
