/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:02:46 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/22 19:07:41 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Return the direction depending on the given numbers.
*/
char	get_direction(int c[2])
{
	if (c[0] == 0)
	{
		if (c[1] == 8)
			return ('d');
		else if (c[1] == -8)
			return ('u');
	}
	else if (c[1] == 0)
	{
		if (c[0] == 8)
			return ('r');
		else if (c[0] == -8)
			return ('l');
	}
	return (0);
}

/**
 * Check if the intended move is possible.
*/
int	is_possible(t_case ***map, char direction, int x, int y)
{
	x -= map[0][0]->sprite->instances->x;
	y -= map[0][0]->sprite->instances->y;
	if (direction == 'u' && (map[y / SIZE_IMG][x / SIZE_IMG]->is_wall
		|| map[y / SIZE_IMG][(x + 63) / SIZE_IMG]->is_wall))
		return (0);
	if (direction == 'd' && (map[(y + 63) / SIZE_IMG][x / SIZE_IMG]->is_wall
		|| map[(y + 63) / SIZE_IMG][(x + 63) / SIZE_IMG]->is_wall))
		return (0);
	if (direction == 'l' && (map[y / SIZE_IMG][x / SIZE_IMG]->is_wall
		|| map[(y + 63) / SIZE_IMG][x / SIZE_IMG]->is_wall))
		return (0);
	if (direction == 'r' && (map[y / SIZE_IMG][(x + 63) / SIZE_IMG]->is_wall
		|| map[(y + 63) / SIZE_IMG][(x + 63) / SIZE_IMG]->is_wall))
		return (0);
	return (1);
}
