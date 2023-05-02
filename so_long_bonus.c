/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:47:13 by ggiboury          #+#    #+#             */
/*   Updated: 2023/05/02 19:48:23 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long_bonus.h"

/**
 * The flood algorithm "fills" every case in the board from the starting point
 * to see if there's a way between multiples point.
*/
void	ft_flood_bonus(t_case ***map, t_node **visited, int x, int y)
{
	if (!is_visited(*visited, x, y))
		add_back(visited, x, y);
	if (!is_visited(*visited, x, y))
	{
		free_nodes(*visited);
		*visited = NULL;
		return ;
	}
	if (!map[y - 1][x]->is_wall && !is_enemy(map[y - 1][x]->ent)
		&& !is_visited(*visited, x, y - 1))
		ft_flood_bonus(map, visited, x, y - 1);
	if (!map[y + 1][x]->is_wall && !is_enemy(map[y + 1][x]->ent)
		&& !is_visited(*visited, x, y + 1))
		ft_flood_bonus(map, visited, x, y + 1);
	if (!map[y][x - 1]->is_wall && !is_enemy(map[y][x - 1]->ent)
		&& !is_visited(*visited, x - 1, y))
		ft_flood_bonus(map, visited, x - 1, y);
	if (!map[y][x + 1]->is_wall && !is_enemy(map[y][x + 1]->ent)
		&& !is_visited(*visited, x + 1, y))
		ft_flood_bonus(map, visited, x + 1, y);
}

void	my_hooks_bonus(void *game)
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
		move(g, p);
		checks_bonus(g, p);
		update_ct(g, 'M');
	}
}

/**
 * Check collisions after the player moved.
*/
void	checks_bonus(t_game *g, t_entity *player)
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
					get_coin_bonus(g, ent);
				else if (ent->n == 'M')
				{
					player->life--;
					ft_printf("You got blackholed ;/\n");
					end(g, player);
				}
				else if (ent->n == 'E')
					end(g, player);
			}
		}
		ent = ent->next;
	}
}

/**
 * Prepare the GUI then start the game.
*/
void	start_bonus(t_case ***map, t_entity *ents)
{
	t_game		game;
	t_entity	*player;

	game.map = map;
	game.ct_movement = 0;
	game.ct_items = get_nb_coin(ents);
	init_ui_bonus(&game, ents);
	build_map(&game);
	build_entities_bonus(&game);
	player = get_entity(ents, 'P');
	render(&game, get_off_x(map, player), get_off_y(map, player));
	render_panel(&game);
	mlx_loop_hook(game.mlx, &my_hooks_bonus, &game);
	mlx_loop(game.mlx);
	errno = 0;
	free_game(game);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_case		***map;
	t_entity	*ents;

	errno = 0;
	if (argc != 2)
		print_error("Usage : ./so_long <fichier.ber>");
	fd = ft_verify_file(argv[1]);
	map = ft_parse_bonus(fd);
	if (map == NULL)
		print_error("Map must be filled with characters");
	ents = get_ents(map);
	if (ents == NULL)
		print_error("Entities allocation failed !");
	map_is_invalid(map, ents);
	if (!map_is_possible_bonus(map, get_entity(ents, 'P'), get_nb_coin(ents)))
		print_error("Unreachable coin or exit");
	start_bonus(map, ents);
	return (0);
}
