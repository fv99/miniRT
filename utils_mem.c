/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khlavaty <khlavaty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:22:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/12 21:09:15 by khlavaty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_map	*malloc_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		error_throw("Cannot allocate memory for map");
	ft_bzero(map, sizeof(t_map));
	map->objects = NULL;
	map->vec_up = (t_float_3){0, 0, 0};
	map->vec_right = (t_float_3){0, 0, 0};
	map->aspect_ratio = 0.0f;
	map->height = 0.0f;
	map->width = 0.0f;
	return (map);
}

void	free_objects(t_obj *objects)
{
	t_obj	*temp;

	while (objects)
	{
		temp = objects;
		if (temp->type == SPHERE)
			free((t_sp *)temp->object);
		else if (temp->type == PLANE)
			free((t_pl *)temp->object);
		else if (temp->type == CYLINDER)
			free((t_cy *)temp->object);
		objects = objects->next;
		free(temp);
	}
}

int	error_throw(char *msg)
{
	ft_printf("\n\tERROR: %s\n", msg);
	exit (-1);
}
