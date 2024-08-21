/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:40:35 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/21 19:45:03 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int create_color(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

// bitwise shift rgb value into hex
int rgb_to_hex(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

t_int_3 extract_rgb(int col)
{
    t_int_3 rgb;

    rgb.x = (col >> 16) & 0xFF;
    rgb.y = (col >> 8) & 0xFF;
    rgb.z = col & 0xFF;
    return (rgb);
}