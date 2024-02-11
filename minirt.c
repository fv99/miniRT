/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:04:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/02/11 19:38:38 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_controls(t_win *win)
{
	mlx_string_put(win->mlx, win->win, 10, 10, 0xFFFFFF, "miniRT");
}

int	handle_destroy_notify(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

// will draw a vertical strip from start_x to end_x
int	render_background(t_win *win, int color, int start_x, int end_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = start_x;
		while (x < end_x)
			mlx_pixel_put(win->mlx, win->win, x++, y, color);
		++y;
	}
	print_controls(win);
	return (0);
}

int	handle_keypress(int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		handle_destroy_notify(win);
	return (render_background(win, 0x000000, 0, WINDOW_WIDTH));
}


int	main(int argc, char **argv)
{
	t_win win;

	if (argc == 2)
	{
		win.mlx = mlx_init();
		win.win = mlx_new_window(win.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
		mlx_hook(win.win, 17, 1L << 17, handle_destroy_notify, &win);
		mlx_hook(win.win, 2, 1L << 0, handle_keypress, &win);
		mlx_loop(win.mlx);
		mlx_destroy_display(win.mlx);
		free(win.mlx);
	}
	else
		ft_printf("Usage: %s <[FILE].rt>\n", argv[0]);
	exit(0);
}