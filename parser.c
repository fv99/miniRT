/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:48:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/06 20:02:48 by fvonsovs         ###   ########.fr       */
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
        map = parse_line(&line, &map);
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
        if (str[i] == '\t' || tmp[i] == '\n')
            str[i] = ' ';
    }
    line = ft_strtrim(str, " ");
    free(str);
    return (line);
}

t_map   parse_line(char *line, t_map *map)
{
    int i;

    i = 0;

    if (line[0] == "\n")
        return ()


}