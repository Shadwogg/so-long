/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:34:21 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 20:03:12 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Returns the y position of the bottom border 
*/
int	get_wall_y(t_game *g)
{
	int		pos_wall;

	pos_wall = g->map[get_y(g->map) - 1][0]->sprite->instances->y;
	return (pos_wall);
}

/**
 * Test if the border is considered by the game too far.
 * Used to know if we need to move the player or the map.
*/
int	is_border_far(t_game *g, t_entity *p, int c[2], char d)
{
	if (d == 'r')
		return ((p->sprite->instances->x + c[0] >= SIZE_IMG * 12
				&& get_wall_x(g) - (p->sprite->instances->x + c[0]) > 192));
	else if (d == 'd')
		return (p->sprite->instances->y + c[1] >= SIZE_IMG * 12
			&& get_wall_y(g) - (p->sprite->instances->y + c[1]) > 192);
	else if (d == 'l')
		return (p->sprite->instances->x + c[0] <= SIZE_IMG * 3
			&& (p->sprite->instances->x + c[0])
			- g->map[0][0]->sprite->instances->x > 3 * SIZE_IMG);
	else if (d == 'u')
		return (p->sprite->instances->y + c[1] <= SIZE_IMG * 3
			&& (p->sprite->instances->y + c[1])
			- g->map[0][0]->sprite->instances->y > 3 * SIZE_IMG);
	return (0);
}

/**
 * Create and return a new entity.
*/
t_entity	*new_entity(char c, int x, int y)
{
	t_entity	*ent;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
	{
		ft_printf("Error : malloc failed in new_entity");
		return (NULL);
	}
	ent->coo[0] = x * SIZE_IMG;
	ent->coo[1] = y * SIZE_IMG;
	ent->life = 1;
	ent->n = c;
	ent->sprite2 = NULL;
	ent->sprite3 = NULL;
	ent->sprite4 = NULL;
	ent->next = NULL;
	return (ent);
}
