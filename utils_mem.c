/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 15:50:04 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map *malloc_map()
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        error_throw("Cannot allocate memory for map");
    ft_bzero(map, sizeof(t_map));
    map->spheres = NULL;
    map->cylinders = NULL;
    map->planes = NULL;
    return map;
}

void free_spheres(t_sp *spheres)
{
    t_sp *current = spheres;
    t_sp *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_planes(t_pl *planes)
{
    t_pl *current = planes;
    t_pl *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_cylinders(t_cy *cylinders)
{
    t_cy *current = cylinders;
    t_cy *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_objects(t_map *map)
{
    free_spheres(map->spheres);
    free_planes(map->planes);
    free_cylinders(map->cylinders);
}