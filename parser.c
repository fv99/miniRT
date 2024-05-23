/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:48:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:40:12 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// free map later!
t_map *parser(char *filename)
{
    t_map *map;
    int fd;
    char *line;

    map = malloc_map();
    fd = open_file(filename);

    line = get_next_line(fd);
    while (line != NULL)
    {
        line = sanitize(line);
        parse_line(map, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (map);
}

char *sanitize(char *line)
{
    int i;
    char *str;

    i = -1;
    str = line;
    while (str && str[++i])
    {
        if (str[i] == '\t' || str[i] == '\n')
            str[i] = ' ';
    }

    line = ft_strtrim(str, " ");
    free(str);
    return (line);
}

int parse_line(t_map *map, char *line)
{
    if (ft_strncmp(line, "A", 1) == 0)
        return parse_ambient(map, line);
    if (ft_strncmp(line, "C", 1) == 0)
        return parse_camera(map, line);
    if (ft_strncmp(line, "L", 1) == 0)
        return parse_light(map, line);
    return (0);
}

int parse_float(char *str, float *num)
{
    if (!is_float(str))
        return 1;
    *num = str_to_float(str);
    return (0);
}

int parse_ulong(char *str, size_t *num)
{
    if (!is_ulong(str))
        return 1;
    *num = (size_t)ft_atoi(str);
    return (0);
}
