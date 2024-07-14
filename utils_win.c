/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:05:14 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/07/14 17:17:18 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int create_color(float r, float g, float b)
{
    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

void	pixel_to_img(t_win *win, int x, int y, int color)
{
    char    *pixel;
    int		i;

    i = win->bpp - 8;
    pixel = win->addr + (y * win->line_l + x * (win->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (win->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (win->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}