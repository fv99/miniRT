/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:50:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:40:12 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_sphere(t_map *map, char *line)
{
    int     i;
    char    **params;

    i = 0;
    params = ft_split(line, ' ');

    // todo

    free(line);
    return (0);
}