/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:01:49 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/22 18:25:31 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Move the map instead of the player to create the illusion
 * that we are still moving.
*/
void	move_map(t_game *g, t_entity *p, int x, int y)
{
	int	ct;
	int	ct2;

	ct = -1;
	while (g->map[++ct])
	{
		ct2 = -1;
		while (g->map[ct][++ct2])
		{
			if (g->map[ct][ct2]->ent && g->map[ct][ct2]->ent != p
				&& g->map[ct][ct2]->ent->sprite->enabled)
			{
				g->map[ct][ct2]->ent->sprite->instances->x -= x;
				g->map[ct][ct2]->ent->sprite->instances->y -= y;
			}
			g->map[ct][ct2]->sprite->instances->x -= x;
			g->map[ct][ct2]->sprite->instances->y -= y;
		}
	}
}
