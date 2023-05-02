/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:41:22 by ggiboury          #+#    #+#             */
/*   Updated: 2023/05/02 19:48:13 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Prepare the view, then start the game.
*/
void	start(t_case ***map, t_entity *ents)
{
	t_game		game;
	t_entity	*player;

	game.map = map;
	game.ct_movement = 0;
	game.ct_items = get_nb_coin(ents);
	init_ui(&game, ents);
	build_map(&game);
	build_entities(&game);
	player = get_entity(ents, 'P');
	render(&game, get_off_x(map, player), get_off_y(map, player));
	mlx_loop_hook(game.mlx, &my_hooks, &game);
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
	map = ft_parse(fd);
	if (map == NULL)
		print_error("Map must be filled with characters");
	ents = get_ents(map);
	if (ents == NULL)
		print_error("Entities allocation failed !");
	map_is_invalid(map, ents);
	if (!map_is_possible(map, get_entity(ents, 'P'), get_nb_coin(ents)))
		print_error("Unreachable coin or exit");
	start(map, ents);
	return (0);
}
