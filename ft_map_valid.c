/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:31 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/26 19:37:08 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Test if the line contains only box of wall.
*/
int	line_is_wall(t_case **line)
{
	int	ct;

	ct = 0;
	while (line[ct] != NULL)
	{
		if (!line[ct]->is_wall)
		{
			ft_printf("Map must have boarding walls.\n");
			return (0);
		}
		ct++;
	}
	return (1);
}

/**
 * Test if the map has wall at the edges of the board.
*/
int	map_is_rectangular(t_case ***map)
{
	int	ct;
	int	y;
	int	x;

	ct = 0;
	y = get_y(map) - 1;
	x = get_x(map) - 1;
	if (!line_is_wall(map[0]) || !line_is_wall(map[y]))
		return (0);
	while (y > 1)
	{
		if (!map[y][0]->is_wall || !map[y][x]->is_wall)
			return (0);
		y--;
	}
	return (1);
}

int	map_has_duplicates(t_case ***map)
{
	int	ct;
	int	ct2;
	int	ct_p;
	int	ct_e;

	ct = -1;
	ct_p = 0;
	ct_e = 0;
	while (map[++ct] != NULL)
	{
		ct2 = -1;
		while (map[ct][++ct2] != NULL)
		{
			if (map[ct][ct2]->ent != NULL)
			{
				if (map[ct][ct2]->ent->n == 'P')
					ct_p++;
				else if (map[ct][ct2]->ent->n == 'E')
					ct_e++;
			}
		}
	}
	return (ct_p != 1 || ct_e != 1);
}

/**
 * Tests if the map has a invalid configuration.
 * If it does, it free the map and entities, then exit the program.
*/
void	map_is_invalid(t_case ***map, t_entity *ent)
{
	int	items;

	if (!map_is_rectangular(map))
	{
		free_map(map);
		print_error("Map's shape should be rectangular");
	}
	if (map_has_duplicates(map))
	{
		free_map(map);
		print_error("Map should not have duplicates exit or player");
	}
	items = get_nb_coin(ent);
	if (items == 0)
	{
		free_map(map);
		print_error("Not enough coins");
	}
}

/**
 * Test if the box is valid.
*/
int	case_is_valid(t_case *box)
{
	if (box->ent != NULL)
	{
		if (box->ent->n == 'P' || box->ent->n == 'C' || box->ent->n == 'E')
			return (1);
		return (0);
	}
	return (1);
}
