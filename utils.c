/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/02/20 19:49:58 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map   *malloc_map()
{
    t_map *map;
    
    map = malloc(sizeof(t_map));
    if (map == NULL)
        error_throw("Cannot malloc map");
    map->amb = NULL;
    map->cam = NULL;
    map->light = NULL;

    return map;
}
