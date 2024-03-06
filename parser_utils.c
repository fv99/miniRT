/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:04 by fvonsovs          #+#    #+#             */
/*   Updated: 2024/03/06 21:15:14 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// returns open file descriptor - manually close after!
int open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_throw("Cannot open file");
    if (!is_rt_file(filename))
        error_throw("Not an .rt file");
    return(fd);
}

int	is_rt_file(char *filename)
{
	int	len;

	len = ft_strlen(filename) - 3;
	if (len > 3)
		return (ft_strncmp(filename + len, ".rt", 3) == 0);
	return (0);
}

// bitwise shift rgb value into hex
int rgb_to_hex(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int error_throw(char *msg)
{
    ft_printf("\n\tERROR: %s\n", msg);
    exit(-1);
}

