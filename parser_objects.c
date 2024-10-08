/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:50:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/14 14:45:33 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_map *map, char *line)
{
	int		i;
	char	**params;
	t_sp	*new;

	i = 0;
	new = (t_sp *)malloc(sizeof(t_sp));
	if (!new)
		error_throw("Failed to malloc sphere");
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
		return (error_throw("Invalid number of sphere params"));
	while (params && params[++i])
	{
		if (i == 1 && parse_xyz_float(params[i], &new->pos))
			return (error_throw("Cannot parse sphere coord"));
		if (i == 2 && parse_float(params[i], &new->dia))
			return (error_throw("Cannot parse sphere diameter"));
		if (i == 3 && parse_color(params[i], &new->col))
			return (error_throw("Cannot parse sphere color"));
	}
	new->next = NULL;
	add_object(map, SPHERE, new, new->col);
	free_array(params);
	return (0);
}

int	parse_plane(t_map *map, char *line)
{
	int		i;
	char	**params;
	t_pl	*new;

	i = 0;
	new = (t_pl *)malloc(sizeof(t_pl));
	if (!new)
		error_throw("Failed to malloc plane");
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
		return (error_throw("Invalid number of plane params"));
	while (params && params[++i])
	{
		if (i == 1 && parse_xyz_float(params[i], &new->pos))
			return (error_throw("Cannot parse plane coord"));
		if (i == 2 && parse_xyz_float(params[i], &new->vec))
			return (error_throw("Cannot parse plane diameter"));
		if (i == 3 && parse_color(params[i], &new->col))
			return (error_throw("Cannot parse plane color"));
	}
	new->next = NULL;
	add_object(map, PLANE, new, new->col);
	free_array(params);
	return (0);
}

int	parse_cylinder(t_map *map, char *line)
{
	int		i;
	char	**params;
	t_cy	*new;

	i = 0;
	new = (t_cy *)malloc(sizeof(t_cy));
	params = ft_split(line, ' ');
	if (!new || array_length(params) != 6)
		return (error_throw("Invalid no. of cylinder params / malloc fail"));
	while (params && params[++i])
	{
		if (i == 1 && parse_xyz_float(params[i], &new->pos))
			return (error_throw("Cannot parse cylinder coord"));
		if (i == 2 && parse_xyz_float(params[i], &new->vec))
			return (error_throw("Cannot parse cylinder vector"));
		if (i == 3 && parse_float(params[i], &new->dia))
			return (error_throw("Cannot parse cylinder diameter"));
		if (i == 4 && parse_float(params[i], &new->hth))
			return (error_throw("Cannot parse cylinder height"));
		if (i == 5 && parse_color(params[i], &new->col))
			return (error_throw("Cannot parse cylinder color"));
	}
	add_object(map, CYLINDER, new, new->col);
	free_array(params);
	return (0);
}
