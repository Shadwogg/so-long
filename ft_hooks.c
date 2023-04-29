/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:20:26 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/26 20:34:20 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Move the player on the model board.
 * Update the position of the player.
*/
void	move_player_map(t_case ***map, t_entity *p, int ct, int ct2)
{
	int			coo[2];
	t_entity	*tmp;

	p->coo[0] = p->sprite->instances->x / SIZE_IMG;
	p->coo[1] = p->sprite->instances->y / SIZE_IMG;
	ct = -1;
	while (map[++ct])
	{
		ct2 = -1;
		while (map[ct][++ct2])
		{
			if (map[ct][ct2]->ent == p)
			{
				tmp = map[ct][ct2]->ent;
				coo[0] = ct2;
				coo[1] = ct;
			}
		}
	}
	if (map[p->coo[1]][p->coo[0]]->ent != p
		&& map[p->coo[1]][p->coo[0]]->ent == NULL)
	{
		map[coo[1]][coo[0]]->ent = map[p->coo[1]][p->coo[0]]->ent;
		map[p->coo[1]][p->coo[0]]->ent = tmp;
	}
}

/**
 * Update the player on the map, or
 * the position of the map depending on the player.
*/
void	update_coo(t_game *g, t_entity *p, int c[2], char d)
{
	if (is_border_far(g, p, c, d))
		move_map(g, p, c[0], c[1]);
	else
	{
		p->sprite->instances->x += c[0];
		p->sprite->instances->y += c[1];
		move_player_map(g->map, p, 0, 0);
	}
	g->ct_movement += 1;
}

/**
 * Check if the player is moving,
 * then update the position if necessary.
 * Return true if the player moved.
*/
int	move(t_game *g, t_entity *p)
{
	int	c[2];

	c[0] = 0;
	c[1] = 0;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W) && is_possible(g->map,
			'u', p->sprite->instances->x, p->sprite->instances->y - 8))
		c[1] = -8;
	else if (mlx_is_key_down(g->mlx, MLX_KEY_D) && is_possible(g->map,
			'r', p->sprite->instances->x + 8, p->sprite->instances->y))
		c[0] = 8;
	else if (mlx_is_key_down(g->mlx, MLX_KEY_S) && is_possible(g->map,
			'd', p->sprite->instances->x, p->sprite->instances->y + 8))
		c[1] = 8;
	else if (mlx_is_key_down(g->mlx, MLX_KEY_A) && is_possible(g->map,
			'l', p->sprite->instances->x - 8, p->sprite->instances->y))
		c[0] = -8;
	if (c[0] != 0 || c[1] != 0)
	{
		update_coo(g, p, c, get_direction(c));
		return (1);
	}
	return (0);
}

void	my_hooks(void *game)
{
	t_game		*g;
	t_entity	*p;

	g = game;
	p = get_entity(g->entities, 'P');
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("Fin du programme.\n");
		mlx_close_window(g->mlx);
	}
	if (g->mlx->delta_time > 0.015)
	{
		if (move(g, p))
			print_on_mov(g->ct_movement);
		checks(g, p);
	}
}
