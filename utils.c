/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/06/13 16:12:52 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_map *malloc_map()
{
    t_map *map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        error_throw("Cannot allocate memory for map");
    ft_bzero(map, sizeof(t_map));
    return map;
}
