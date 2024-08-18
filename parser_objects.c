/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:50:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/18 22:27:40 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_sphere(t_map *map, char *line)
{
    int     i;
    char    **params;
    t_sp    *new;

    i = 0;
    new = (t_sp *)malloc(sizeof(t_sp));
    if (!new)
        return error_throw("Failed to malloc sphere"); // over 25 lines maybe remove this later
    params = ft_split(line, ' ');
    if (array_length(params) != 4)
        return error_throw("Invalid number of sphere params");
    while (params && params[++i])
    {
        if (i == 1 && parse_xyz_float(params[i], &new->pos))
            return error_throw("Cannot parse sphere coord");
        if (i == 2 && parse_float(params[i], &new->dia))
            return error_throw("Cannot parse sphere diameter");
        if (i == 3 && parse_color(params[i], &new->col))
            return error_throw("Cannot parse sphere color");
    }
    new->next = NULL;
    add_object(map, SPHERE, new);
    free_array(params);
    return (0);
}

int parse_plane(t_map *map, char *line)
{
    int     i;
    char    **params;
    t_pl    *new;

    i = 0;
    new = (t_pl *)malloc(sizeof(t_pl));
    if (!new)
        error_throw("Failed to malloc plane"); // over 25 lines maybe remove this later
    params = ft_split(line, ' ');
    if (array_length(params) != 4)
        return error_throw("Invalid number of plane params");
    while (params && params[++i])
    {
        if (i == 1 && parse_xyz_float(params[i], &new->pos))
            return error_throw("Cannot parse plane coord");
        if (i == 2 && parse_xyz_float(params[i], &new->vec))
            return error_throw("Cannot parse plane diameter");
        if (i == 3 && parse_color(params[i], &new->col))
            return error_throw("Cannot parse plane color");
    }
    new->next = NULL;
    add_object(map, PLANE, new);
    free_array(params);
    return (0);
}

int parse_cylinder(t_map *map, char *line)
{
    int     i;
    char    **params;
    t_cy    *new;

    i = 0;
    new = (t_cy *)malloc(sizeof(t_cy));
    if (!new)
        error_throw("Failed to malloc cylinder"); // over 25 lines maybe remove this later
    params = ft_split(line, ' ');
    if (array_length(params) != 6)
        return error_throw("Invalid number of cylinder params");
    while (params && params[++i])
    {
        if (i == 1 && parse_xyz_float(params[i], &new->pos))
            return error_throw("Cannot parse cylinder coord");
        if (i == 2 && parse_xyz_float(params[i], &new->vec))
            return error_throw("Cannot parse cylinder vector");
        if (i == 3 && parse_float(params[i], &new->dia))
            return error_throw("Cannot parse cylinder diameter");
        if (i == 4 && parse_float(params[i], &new->hth))
            return error_throw("Cannot parse cylinder height");
        if (i == 5 && parse_color(params[i], &new->col))
            return error_throw("Cannot parse cylinder color");
    }
    new->next = NULL;
    add_object(map, CYLINDER, new); 
    free_array(params);
    return (0);
}