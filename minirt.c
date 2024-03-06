/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:04:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/06 19:19:23 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render(t_win *win)
{
	int img_x;
	int img_y;

	print_controls(win);
	
	win->img = mlx_xpm_file_to_image(win->mlx, "cat.xpm", &img_x, &img_y);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, WINDOW_HEIGHT - img_y);

	return (0);
}

int	main(int argc, char **argv)
{
	t_win win;

	if (argc == 2)
	{
		parser(argv);
		win.mlx = mlx_init();
		win.win = mlx_new_window(win.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
		mlx_hook(win.win, 2, 1L << 0, handle_keypress, &win);
		mlx_hook(win.win, 17, 1L << 17, handle_destroy_notify, &win);
		mlx_loop_hook(win.mlx, render, &win);
		mlx_loop(win.mlx);
		mlx_destroy_display(win.mlx);
		free(win.mlx);
	}
	else
		ft_printf("Usage: %s <[FILE].rt>\n", argv[0]);
	exit(0);
}