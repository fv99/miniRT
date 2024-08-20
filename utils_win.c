/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:05:14 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/20 18:35:47 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int ambient_lum(t_map *map)
{
    t_float_3   rgb;
    t_float_3   conv;
    float       lum;
    int         ret;

    lum = map->amb.lum;
    rgb = extract_rgb(map->amb.col);
    conv.x = rgb.x * lum;
    conv.y = rgb.y * lum;
    conv.z = rgb.z * lum;
    ret = create_color(conv.x, conv.y ,conv.z);

    return (ret);
}

void	pixel_to_img(t_win *win, int x, int y, int color)
{
    char    *pixel;
    int		i;

    i = win->bpp - 8;
    pixel = win->addr + (y * win->line_l + x * (win->bpp / 8));
    while (i >= 0)
    {
        // big endian, MSB is the leftmost bit
        if (win->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        // little endian, LSB is the leftmost bit
        else
            *pixel++ = (color >> (win->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

