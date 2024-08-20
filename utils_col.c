/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:40:35 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/20 18:45:13 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int create_color(float r, float g, float b)
{
    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

// bitwise shift rgb value into hex
int rgb_to_hex(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

t_float_3 extract_rgb(int col)
{
    t_float_3 rgb;

    rgb.x = ((col >> 16) & 0xFF) / 255.0f;
    rgb.y = ((col >> 8) & 0xFF) / 255.0f;
    rgb.z = (col & 0xFF) / 255.0f;
    return (rgb);
}
