/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_features.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:58:03 by khlavaty          #+#    #+#             */
/*   Updated: 2024/09/12 18:00:08 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_objects(t_win *win, int keysym)
{
	if (keysym == KEY_W)
		translate_objects(win, 0.1, 'y');
	else if (keysym == KEY_S)
		translate_objects(win, -0.1, 'y');
	else if (keysym == KEY_A)
		translate_objects(win, -0.1, 'x');
	else if (keysym == KEY_D)
		translate_objects(win, 0.1, 'x');
	else if (keysym == KEY_Q)
		translate_objects(win, -0.1, 'z');
	else if (keysym == KEY_E)
		translate_objects(win, 0.1, 'z');
}

void	move_light(t_win *win, int keysym)
{
	if (keysym == KEY_I)
		win->map->light.pos.y += 0.1;
	else if (keysym == KEY_K)
		win->map->light.pos.y -= 0.1;
	else if (keysym == KEY_J)
		win->map->light.pos.x -= 0.1;
	else if (keysym == KEY_L)
		win->map->light.pos.x += 0.1;
	else if (keysym == KEY_U)
		win->map->light.pos.z -= 0.1;
	else if (keysym == KEY_O)
		win->map->light.pos.z += 0.1;
}

void	move_camera(t_win *win, int keysym)
{
	if (keysym == KEY_T)
		win->map->cam.pos.y -= 0.1;
	else if (keysym == KEY_G)
		win->map->cam.pos.y += 0.1;
	else if (keysym == KEY_F)
		win->map->cam.pos.x -= 0.1;
	else if (keysym == KEY_H)
		win->map->cam.pos.x += 0.1;
	else if (keysym == KEY_R)
		win->map->cam.pos.z -= 0.1;
	else if (keysym == KEY_Y)
		win->map->cam.pos.z += 0.1;
}
