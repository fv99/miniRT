/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:38:30 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/09/14 15:09:51 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// initializes map viewport
// sets default vector if camera vector is set to zero
// calculates right vector and up vector of the camera
void	camera_init(t_map *map)
{
	if (is_zero_vector(map->cam.vec))
		map->cam.vec = (t_float_3){0.0f, 0.0f, -1.0f};
	map->aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	map->width = tan((map->cam.fov / 2.0) * (PI / 180.0));
	map->height = map->width / map->aspect_ratio;
	map->vec_right = vec_normalize(vec_cross(map->cam.vec, \
	(t_float_3){0.0, -1.0, 0.0}));
	map->vec_up = vec_normalize(vec_cross(map->vec_right, map->cam.vec));
}

// converts pixel position into 3d point on a normalized plane
// ((2.0f * x) / width) - 1 - maps pixel x from screen to viewport
t_float_3	pixels_to_viewport(int x, int y)
{
	t_float_3	ret;
	float		width;
	float		height;

	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	ret.x = ((2.0f * x) / width) - 1;
	ret.y = ((2.0f * y) / height) - 1;
	ret.z = 1.0f;
	return (ret);
}

// throws an infinite ray in space from the camera 
// in the direction of the vector
t_ray	throw_ray(t_map *map, t_float_3 vec)
{
	t_ray		ray;
	t_float_3	vert;
	t_float_3	horiz;
	t_float_3	result;

	vert = vec_mul(map->vec_up, vec.y * map->height);
	horiz = vec_mul(map->vec_right, vec.x * map->width);
	result = vec_add(vert, horiz);
	result = vec_add(result, map->cam.vec);
	result = vec_add(result, map->cam.pos);
	ray.orig = map->cam.pos;
	ray.dir = vec_normalize(vec_sub(result, ray.orig));
	return (ray);
}
