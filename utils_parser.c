/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 20:59:33 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// returns open file descriptor - manually close after!
int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_throw("Cannot open file");
	if (!is_rt_file(filename))
		error_throw("Not an .rt file");
	return (fd);
}

int	is_rt_file(char *filename)
{
	int	len;

	len = ft_strlen(filename) - 3;
	if (len > 3)
		return (ft_strncmp(filename + len, ".rt", 3) == 0);
	return (0);
}

void	add_object(t_map *map, t_obj_type type, void *object, int col)
{
	t_obj	*new_obj;

	new_obj = malloc(sizeof(t_obj));
	new_obj->type = type;
	new_obj->object = object;
	new_obj->color = col;
	new_obj->next = map->objects;
	new_obj->id = rand();
	map->objects = new_obj;
}
