/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:04:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/25 12:36:31 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render(t_win *win)
{
	print_controls(win);

	return (0);
}

int	main(int argc, char **argv)
{
	// t_win win;
	t_map *map;

	if (argc != 2)
		exit(ft_printf("Usage: %s <[FILE].rt>\n", argv[0]));

	map = parser(argv[1]); // free this later
	test_parser(map);
	free_objects(map);
	free(map);

	// win.mlx = mlx_init();
	// win.win = mlx_new_window(win.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	// mlx_hook(win.win, 2, 1L << 0, handle_keypress, &win);
	// mlx_hook(win.win, 17, 1L << 17, handle_destroy_notify, &win);
	// mlx_loop_hook(win.mlx, render, &win);
	// mlx_loop(win.mlx);
	// mlx_destroy_window(win.mlx, win.win);
	// free(win.mlx);

	exit(0);
}