/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/09 15:29:53 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map *malloc_map()
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        error_throw("Cannot allocate memory for map");
    ft_bzero(map, sizeof(t_map));
    map->objects = NULL;
    return map;
}

void free_objects(t_obj *objects)
{
    t_obj *temp;

    while (objects)
    {
        temp = objects;
        if (temp->type == sphere)
            free((t_sp *)temp->object);
        else if (temp->type == plane)
            free((t_pl *)temp->object);
        else if (temp->type == cylinder)
            free((t_cy *)temp->object);
        objects = objects->next;
        free(temp);
    }
}
