/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:23:52 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/19 18:38:48 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Free the game then print s.
*/
void	free2_print_error(t_game *g, char *s)
{
	free_game(*g);
	print_error(s);
}

/**
 * Test if the textures exists.
*/
void	test_textures(t_game *g)
{
	int	fd;

	fd = open("img/starry_background.png", S_IRWXU);
	if (fd == -1)
		free2_print_error(g, "starry_background.png ");
	close(fd);
	fd = open("img/asteroids.png", S_IRWXU);
	if (fd == -1)
		free2_print_error(g, "asteroids.png ");
	close(fd);
	fd = open("img/player.png", S_IRWXU);
	if (fd == -1)
		free2_print_error(g, "player.png ");
	close(fd);
	fd = open("img/Lightdust.png", S_IRWXU);
	if (fd == -1)
		free2_print_error(g, "Lightdust.png ");
	close(fd);
	fd = open("img/exit.png", S_IRWXU);
	if (fd == -1)
		free2_print_error(g, "exit.png ");
	close(fd);
}

/**
 * Initialise the textures used.
*/
mlx_texture_t	**init_textures(t_game *g)
{
	mlx_texture_t	**new;

	test_textures(g);
	new = malloc(6 * sizeof(mlx_texture_t *));
	if (new == NULL)
		return (NULL);
	new[0] = mlx_load_png("img/starry_background.png");
	if (!new[0])
		free2_print_error(g, "Can't find textures of the ground");
	new[1] = mlx_load_png("img/asteroids.png");
	if (!new[1])
		free2_print_error(g, "Can't find textures of walls");
	new[2] = mlx_load_png("img/player.png");
	if (!new[2])
		free2_print_error(g, "Can't find textures of the player");
	new[3] = mlx_load_png("img/Lightdust.png");
	if (!new[3])
		free2_print_error(g, "Can't find textures of the collectibles");
	new[4] = mlx_load_png("img/exit.png");
	if (!new[4])
		free2_print_error(g, "Can't find textures of the exit");
	new[5] = NULL;
	return (new);
}

/**
 * Initialize the user interface and textures.
*/
int	init_ui(t_game *game, t_entity *ents)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "so_long", false);
	errno = 0;
	if (game->mlx == NULL)
	{
		free_map(game->map);
		print_error("Mlx failed to be initialized.");
	}
	game->entities = ents;
	game->textures = NULL;
	game->textures = init_textures(game);
	if (game->textures == NULL)
	{
		free_map(game->map);
		print_error("Malloc error in init_texture()");
	}
	return (1);
}

/**
 * Give each box it's own sprite.
*/
void	build_map(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (g->map[++y] != NULL)
	{
		x = -1;
		while (g->map[y][++x] != NULL)
		{
			if (g->map[y][x]->is_wall)
				g->map[y][x]->sprite
					= mlx_texture_to_image(g->mlx, g->textures[1]);
			else
				g->map[y][x]->sprite
					= mlx_texture_to_image(g->mlx, g->textures[0]);
			if (g->map[y][x]->sprite == NULL)
				print_error("Mlx failed to do its job.");
		}
	}
}
