/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:38:20 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/21 13:18:39 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int test_map(t_map *map)
{
    if (!map)
        return(ft_printf("Invalid map: NULL pointer\n"));
    if (!map->amb)
        return(ft_printf("Invalid map: Ambient lighting not set\n"));
    if (!map->cam)
        return(ft_printf("Invalid map: Camera not set\n"));
    if (!map->cam->pos)
        return(ft_printf("Invalid map: Camera position not set\n"));
    if (!map->cam->vec)
        return(ft_printf("Invalid map: Camera vector not set\n"));
    if (!map->light)
        return(ft_printf("Invalid map: Light point not set\n"));
    if (!map->light->pos)
        return(ft_printf("Invalid map: Light point position not set\n"));
    return (ft_printf("\tMap OK! \n"));
}

int test_parser(t_map *map)
{
    printf("\nAmbient lighting:\n");
    printf("  Lum: %.2f\n", map->amb->lum);
    printf("  Col: 0x%06X\n", map->amb->col);
    
    // printf("\nCamera:\n");
    // printf("  Position: (%.2f, %.2f, %.2f)\n", map->cam->pos->x, map->cam->pos->y, map->cam->pos->z);
    // printf("  Vector: (%.2f, %.2f, %.2f)\n", map->cam->vec->x, map->cam->vec->y, map->cam->vec->z);
    // printf("  FOV: %d\n", map->cam->fov);

    // printf("\nLight point:\n");
    // printf("  Position: (%.2f, %.2f, %.2f)\n", map->light->pos->x, map->light->pos->y, map->light->pos->z);
    // printf("  Lum: %.2f\n", map->light->lum);
    // printf("  Col: %06X\n", map->light->col);
    return (0);
}
