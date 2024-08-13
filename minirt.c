/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:04:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/13 20:05:51 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int close_window(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
    t_win win;
    t_map *map;

    if (argc != 2)
        exit(ft_printf("Usage: %s <[FILE].rt>\n", argv[0]));

    map = parser(argv[1]); // free this later
    test_parser(map);

    win.map = map;
    win.mlx = mlx_init();
    win.win = mlx_new_window(win.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
    win.img = mlx_new_image(win.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.endian);

    // printf("bpp: %d, line_l: %d, endian: %d\n", win.bpp, win.line_l, win.endian); // debug
	// draw_gradient(&win); // debug
	// mlx_put_image_to_window(win.mlx, win.win, win.img, 0, 0);

    mlx_loop_hook(win.mlx, render, &win);
    mlx_hook(win.win, 2, 1L << 0, handle_keypress, &win);
	mlx_hook(win.win, 17, 0, close_window, &win);
    mlx_loop(win.mlx);


    // free_objects(map);
    // free(win.map);
    // free(map);
    // free(win.mlx);
    return(0);
}