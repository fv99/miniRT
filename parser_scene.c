/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:31:29 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/08/05 15:44:43 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_ambient(t_map *map, char *line)
{
    int i;
    char **params;

    i = 0;
    params = ft_split(line, ' ');
    if (array_length(params) != 3)
        return error_throw("Invalid number of ambient params");

    while (params && params[++i])
    {
        if (i == 1 && parse_float(params[i], &map->amb.lum))
            return error_throw("Cannot parse float");
        if (i == 2 && parse_color(params[i], &map->amb.col))
            return error_throw("Cannot parse color");
    }
    map->amb.amb = ambient_lum(map);
    free_array(params);
    return (0);
}

int parse_camera(t_map *map, char *line)
{
    int i;
    char **params;

    i = 0;
    params = ft_split(line, ' ');
    if (array_length(params) != 4)
        return error_throw("Invalid number of camera params");

    while (params && params[++i])
    {
        if (i == 1 && parse_xyz_float(params[i], &map->cam.pos))
            return error_throw("Cannot parse cam position");
        if (i == 2 && parse_xyz_float(params[i], &map->cam.vec))
            return error_throw("Cannot parse cam vector");
        if (i == 3 && parse_ulong(params[i], &map->cam.fov))
            return error_throw("Cannot parse cam fov");
    }

    free_array(params);
    return (0);
}

int parse_light(t_map *map, char *line)
{
    int i;
    char **params;

    i = 0;
    params = ft_split(line, ' ');
    if (array_length(params) != 4)
        return error_throw("Invalid number of camera params");

    while (params && params[++i])
    {
        if (i == 1 && parse_xyz_float(params[i], &map->light.pos))
            return error_throw("Cannot parse light position");
        if (i == 2 && parse_float(params[i], &map->light.lum))
            return error_throw("Cannot parse light lum");
        if (i == 3 && parse_color(params[i], &map->light.col))
            return error_throw("Cannot parse light color");
    }

    free_array(params);
    return (0);
}

int parse_color(char *str, int *col)
{
    char **colors;
    int rgb[3];
    int i;
    int x;

    i = 0;
    x = 0;
    colors = ft_split(str, ',');
    if (array_length(colors) < 1)
        return 0;
    while (colors && colors[i])
    {
        rgb[x] = ft_atoi(colors[i]);
        x++;
        i++;
    }
    *col = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
    free_array(colors);
    return (0);
}

int parse_xyz_float(char *str, t_float_3 *coord)
{
    char **coords;

    coords = ft_split(str, ',');
    if (array_length(coords) != 3)
    {
        free_array(coords);
        return error_throw("Invalid number of coordinates");
    }
    coord->x = str_to_float(coords[0]);
    coord->y = str_to_float(coords[1]);
    coord->z = str_to_float(coords[2]);
    free_array(coords);
    return (0);
}
