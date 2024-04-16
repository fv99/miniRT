/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/21 13:18:03 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map   *malloc_map()
{
    t_map *map;
    
    map = (t_map *)malloc(sizeof(t_map));
    if (map == NULL)
        error_throw("Cannot malloc map");

    map->amb->col = 0x000000;
    map->amb->lum = 0;
    map->light = NULL;

    return map;
}

void    free_map(t_map *map)
{
    if (map == NULL)
        return;
    if (map->amb != NULL)
    {
        free(map->amb);
        map->amb = NULL;
    }
    if (map->cam != NULL)
    {
        free(map->cam->pos);
        free(map->cam->vec);
    }
    free(map);
}
