/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:24:39 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/14 16:49:44 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_destroy_notify(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

// handle keypress events
// move camera in x, y, z direction arrow keys
// move camera in z direction with w, s keys
// same for light source
int	handle_keypress(int keysym, t_win *win)
{
	if (keysym == KEY_ESC)
		handle_destroy_notify(win);
	else if (keysym == KEY_UP)
	{
		win->map->cam.vec.y -= 0.1;
		win->map->light.pos.y -= 5.0;
	}
	else if (keysym == KEY_DOWN)
	{
		win->map->cam.vec.y += 0.1;
		win->map->light.pos.y += 5.0;
	}
	else if (keysym == KEY_LEFT)
	{
		win->map->cam.vec.x -= 0.1;
		win->map->light.pos.x -= 5.0;
	}
	else if (keysym == KEY_RIGHT)
	{
		win->map->cam.vec.x += 0.1;
		win->map->light.pos.x += 5.0;
	}
	else if (keysym == KEY_W)
	{
		win->map->cam.vec.z -= 0.1;
		win->map->light.pos.z -= 5.0;
	}
	else if (keysym == KEY_S)
	{
		win->map->cam.vec.z += 0.1;
		win->map->light.pos.z += 5.0;
	}
	return (0);
}

int	print_controls(t_win *win)
{
	mlx_string_put(win->mlx, win->win, 10, 10, 0xFFFFFF, "miniRT");
	return (0);
}
