/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:35:09 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map *malloc_map()
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        error_throw("Cannot allocate memory for map");
    ft_bzero(map, sizeof(t_map));  // Initialize memory to zero
    return map;
}
