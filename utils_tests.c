/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:38:20 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:23 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int test_map(int fd)
{
    char *line;
    int a;
    int l;
    int c; 

    a = 0;
    l = 0;
    c = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (*line == 'A')
            a++;
        else if (*line == 'L')
            l++;
        else if (*line == 'C') 
            c++;
        free(line);
        line = get_next_line(fd);
    }
    if (a > 1 || l > 1 || c > 1)
        error_throw("Invalid map - element already defined");
    return (ft_printf("\nMap OK!\n"));
}

int test_parser(t_map *map)
{
    t_sp *current_sphere;
    t_pl *current_plane;
    t_cy *current_cylinder;
    int plane_index = 0;
    int sphere_index = 0;
    int cylinder_index = 0;

    printf("\nAmbient lighting:\n");
    printf("  Lum: %.2f\n", map->amb.lum);
    printf("  Col: 0x%06X\n", map->amb.col);
    
    printf("\nCamera:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", map->cam.pos.x, map->cam.pos.y, map->cam.pos.z);
    printf("  Vector: (%.2f, %.2f, %.2f)\n", map->cam.vec.x, map->cam.vec.y, map->cam.vec.z);
    printf("  FOV: %zu\n", map->cam.fov);

    printf("\nLight point:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", map->light.pos.x, map->light.pos.y, map->light.pos.z);
    printf("  Lum: %.2f\n", map->light.lum);
    printf("  Col: 0x%06X\n", map->light.col);

    printf("\nSpheres:\n");
    current_sphere = map->spheres;
    while (current_sphere != NULL)
    {
        printf("\tSphere %d:\n", sphere_index);
        printf("  Position: (%.2f, %.2f, %.2f)\n", current_sphere->pos.x, current_sphere->pos.y, current_sphere->pos.z);
        printf("  Diameter: %.2f\n", current_sphere->dia);
        printf("  Color: 0x%06X\n\n", current_sphere->col);
        
        current_sphere = current_sphere->next;
        sphere_index++;
    }

    printf("\nPlanes:\n");
    current_plane = map->planes;
    while (current_plane != NULL)
    {
        printf("\tPlane %d:\n", plane_index);
        printf("  Position: (%.2f, %.2f, %.2f)\n", current_plane->pos.x, current_plane->pos.y, current_plane->pos.z);
        printf("  Vector: (%.2f, %.2f, %.2f)\n", current_plane->vec.x, current_plane->vec.y, current_plane->vec.z);
        printf("  Color: 0x%06X\n\n", current_plane->col);

        current_plane = current_plane->next;
        plane_index++;
    }

    printf("\nCylinders:\n");
    current_cylinder = map->cylinders;
    while (current_cylinder != NULL)
    {
        printf("\tCylinder %d:\n", cylinder_index);
        printf("  Position: (%.2f, %.2f, %.2f)\n", current_cylinder->pos.x, current_cylinder->pos.y, current_cylinder->pos.z);
        printf("  Vector: (%.2f, %.2f, %.2f)\n", current_cylinder->vec.x, current_cylinder->vec.y, current_cylinder->vec.z);
        printf("  Diameter: %.2f\n", current_cylinder->dia);
        printf("  Height: %.2f\n", current_cylinder->hth);
        printf("  Color: 0x%06X\n\n", current_cylinder->col);

        current_cylinder = current_cylinder->next;
        cylinder_index++;
    }
    return 0;
}

