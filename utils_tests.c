/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:38:20 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:23 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int test_map(int fd)
{
    char *line;
    int a;
    int l;
    int c; 

    a = 0;
    l = 0;
    c = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (*line == 'A')
            a++;
        else if (*line == 'L')
            l++;
        else if (*line == 'C') 
            c++;
        free(line);
        line = get_next_line(fd);
    }
    if (a > 1 || l > 1 || c > 1)
        error_throw("Invalid map - element already defined");
    return (ft_printf("\nMap OK!\n"));
}

int test_parser(t_map *map)
{
    printf("\nAmbient lighting:\n");
    printf("  Lum: %.2f\n", map->amb.lum);
    printf("  Col: 0x%06X\n", map->amb.col);
    
    printf("\nCamera:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", map->cam.pos.x, map->cam.pos.y, map->cam.pos.z);
    printf("  Vector: (%.2f, %.2f, %.2f)\n", map->cam.vec.x, map->cam.vec.y, map->cam.vec.z);
    printf("  FOV: %zu\n", map->cam.fov);

    printf("\nLight point:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", map->light.pos.x, map->light.pos.y, map->light.pos.z);
    printf("  Lum: %.2f\n", map->light.lum);
    printf("  Col: 0x%06X\n", map->light.col);

    return 0;
}
