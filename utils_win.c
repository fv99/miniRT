/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:05:14 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 20:50:29 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// big endian, MSB is the leftmost bit
// little endian, LSB is the leftmost bit
void	pixel_to_img(t_win *win, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = win->bpp - 8;
	pixel = win->addr + (y * win->line_l + x * (win->bpp / 8));
	while (i >= 0)
	{
		if (win->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (win->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
