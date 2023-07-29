/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:13:08 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 23:11:13 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Check collisions after the player moved.
*/
void	checks(t_game *g, t_entity *player)
{
	t_entity	*ent;

	ent = g->entities;
	while (ent != NULL)
	{
		if (ent != player)
		{
			if (collision(player, ent))
			{
				if (ent->n == 'C')
					get_coin(g, ent);
				else if (ent->n == 'E')
					end(g, player);
			}
		}
		ent = ent->next;
	}
}

/**
 * Free the memory allocated, then exit the program. 
*/
int	close_game(t_game *g)
{
	mlx_terminate(g->mlx);
	free_game(*g);
	exit(EXIT_SUCCESS);
}

/**
 * Check if the two entities are in the same space.
*/
int	collision(t_entity *p, t_entity *ent)
{
	if (p->sprite->instances->y < ent->sprite->instances->y + SIZE_IMG
		&& p->sprite->instances->y > ent->sprite->instances->y - SIZE_IMG)
	{
		if (p->sprite->instances->x < ent->sprite->instances->x + SIZE_IMG
			&& p->sprite->instances->x > ent->sprite->instances->x - SIZE_IMG)
			return (1);
	}
	return (0);
}

/**
 * If the game is finished, end the game.
 * Does nothing if not.
*/
void	end(t_game *g, t_entity *p)
{
	if (g->ct_items == 0 || p->life == 0)
	{
		if (p->life != 0)
		{
			ft_printf("Congratulations !\n");
			ft_printf("Map resolved in %d moves.\n", g->ct_movement / 8);
		}
		close_game(g);
	}
}

/**
 * Get the coin if the coin is not taken.
*/
void	get_coin(t_game *g, t_entity *coin)
{
	if (coin->sprite->instances->enabled)
	{
		coin->life = 0;
		coin->sprite->instances->enabled = false;
		g->ct_items--;
		if (g->ct_items == 0)
		{
			get_entity(g->entities, 'E')->sprite->instances->enabled = true;
			mlx_delete_image(g->mlx, g->str[1]);
			mlx_delete_image(g->mlx, g->ct2_img);
		}
	}
}
