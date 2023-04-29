/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:50:09 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/06 14:20:39 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Returns the size x (size of a line) of the map.
*/
int	get_x(t_case ***map)
{
	int	ct;

	ct = 0;
	if (map == NULL || *map == NULL)
		return (-1);
	while (map[0][ct] != NULL)
		ct++;
	return (ct);
}

/**
 * Return the size y (number of line) of the map.
*/
int	get_y(t_case ***map)
{
	int	ct;

	ct = 0;
	if (map == NULL || *map == NULL)
		return (-1);
	while (map[ct] != NULL)
		ct++;
	return (ct);
}

/**
 * Returns the offset for the x axis
*/
int	get_off_x(t_case ***map, t_entity *p)
{
	int	offset;
	int	border;

	border = get_x(map);
	if (p->coo[0] < 12 * SIZE_IMG)
		offset = 0;
	else
	{
		offset = 12 * SIZE_IMG - p->coo[0];
		if (SIZE_IMG * border - p->coo[0] < 3 * SIZE_IMG)
			offset += (3 * SIZE_IMG) - ((border - 1) * SIZE_IMG - p->coo[0]);
	}
	return (offset);
}

/**
 * Returns the offset for the y axis
*/
int	get_off_y(t_case ***map, t_entity *p)
{
	int	offset;
	int	border;

	border = get_y(map);
	if (p->coo[1] < 12 * SIZE_IMG)
		offset = 0;
	else
	{
		offset = 12 * SIZE_IMG - p->coo[1];
		if (SIZE_IMG * border - p->coo[1] < 3 * SIZE_IMG)
			offset += (3 * SIZE_IMG) - ((border - 1) * SIZE_IMG - p->coo[1]);
	}
	return (offset);
}
