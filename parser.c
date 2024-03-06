/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:48:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/06 21:15:07 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map   parser(char *filename)
{
    t_map   *map;
    int     fd;
    char    *line;

    fd = open_file(filename);

    line = get_next_line(fd);
    while (line != NULL)
    {
        line = sanitize(line);
        map = parse_line(&map, &line);
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

t_map   parse_line(t_map *map, char *line)
{
    if (ft_strncmp(line, "R", 1) == 0)
        return (parse_ambient(map, line));
    
    return (0);
}

int parse_ambient(t_map *map, char *line)
{
    int     i;
    char    **params;
    t_amb   amb;

    i = 0;
    params = ft_split(line, ' ');
    if (map->amb)
        error_throw("Too many ambients in map");
    if (array_length(params) != 3)
        error_throw("Invalid no. of ambient params");
    ft_bzero(&amb, sizeof(t_amb));
    while (params && params[++i])
    {
        // parse here

    }
    map->amb = amb;
    free_array(params);
    return (0);
}

int	parse_float(char *str, float *num)
{
	if (!is_float(str))
		return (1);
	*num = str_to_float(str);
	return (0);
}

int	parse_ulong(char *str, size_t *num)
{
	if (!is_ulong(str))
		return (1);
	*num = (size_t)ft_atoi(str);
	return (0);
}

