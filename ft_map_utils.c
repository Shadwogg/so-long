/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:50:23 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/19 17:35:25 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Return the number of items to get in the map.
*/
int	get_nb_coin(t_entity *ents)
{
	int			ct_coin;
	t_entity	*cur;

	cur = ents;
	ct_coin = 0;
	while (cur != NULL)
	{
		if (cur->n == 'C')
			ct_coin++;
		cur = cur->next;
	}
	return (ct_coin);
}

/**
 * Return the first entity on the map.
*/
t_entity	*get_first_ent(t_case ***map)
{
	int	ct;
	int	ct2;

	ct = -1;
	while (map[++ct])
	{
		ct2 = -1;
		while (map[ct][++ct2])
		{
			if (map[ct][ct2]->ent != NULL)
				return (map[ct][ct2]->ent);
		}
	}
	return (NULL);
}

/**
 * Return a new list composed of every entity on the map.
*/
t_entity	*get_ents(t_case ***map)
{
	t_entity	*ent;
	t_entity	*cur;
	int			ct;
	int			ct2;

	ct = -1;
	ent = get_first_ent(map);
	if (ent == NULL)
		return (NULL);
	cur = ent;
	while (map[++ct])
	{
		ct2 = -1;
		while (map[ct][++ct2])
		{
			if (map[ct][ct2]->ent != NULL)
			{
				cur->next = map[ct][ct2]->ent;
				cur = cur->next;
			}
		}
	}
	return (ent);
}

/**
 * Returns the first entity met with the name c.
*/
t_entity	*get_entity(t_entity *ents, char c)
{
	t_entity	*p;

	p = ents;
	while (p != NULL)
	{
		if (p->n == c)
			return (p);
		p = p->next;
	}
	return (NULL);
}

/**
 * Returns the x position of the right border 
*/
int	get_wall_x(t_game *g)
{
	int	pos_wall;

	pos_wall = g->map[0][get_x(g->map) - 1]->sprite->instances->x;
	return (pos_wall);
}
