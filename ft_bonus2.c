/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:58:19 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/29 18:16:18 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long_bonus.h"

/**
 * Get the coin if the coin is not taken.
*/
void	get_coin_bonus(t_game *g, t_entity *coin)
{
	if (coin->sprite->instances->enabled)
	{
		coin->life = 0;
		coin->sprite->instances->enabled = false;
		g->ct_items--;
		update_ct(g, 'C');
		if (g->ct_items == 0)
		{
			get_entity(g->entities, 'E')->sprite->instances->enabled = true;
			mlx_delete_image(g->mlx, g->str[1]);
			mlx_delete_image(g->mlx, g->ct2_img);
			g->str[1] = mlx_put_string(g->mlx, "All items recupered.", 0, 20);
		}
	}
}

/**
 * Update the counters.  
*/
void	update_ct(t_game *g, char c)
{
	char	*buf;

	if (c == 'M')
	{
		mlx_delete_image(g->mlx, g->ct_img);
		buf = ft_itos(g->ct_movement / 8);
		g->ct_img = mlx_put_string(g->mlx, buf, 75, 0);
		free(buf);
	}
	else if (c == 'C')
	{
		mlx_delete_image(g->mlx, g->ct2_img);
		buf = ft_itos(g->ct_items);
		g->ct2_img = mlx_put_string(g->mlx, buf, 125, 20);
		free(buf);
	}
}

/**
 * Test if the entity (if existing) is a blackhole.
*/
int	is_enemy(t_entity *ent)
{
	if (ent != NULL)
	{
		printf("%c \n", ent->n);
		return (ent->n == 'M');
	}
	return (0);
}
