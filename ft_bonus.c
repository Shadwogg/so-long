/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:04:21 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 23:17:22 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long_bonus.h"

/**
 * Load textures for the bonus.
*/
mlx_texture_t	**init_textures_bonus(t_game *g)
{
	mlx_texture_t	**new;

	new = malloc(7 * sizeof(mlx_texture_t *));
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
	new[5] = mlx_load_png("img/blackhole.png");
	if (!new[5])
		free2_print_error(g, "Can't find textures of ennemy");
	new[6] = NULL;
	return (new);
}

/**
 * Test if the textures exists.
*/
void	test_textures_bonus(t_game *g)
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
 * Test if the box is valid for the bonus.
*/
int	case_is_valid_bonus(t_case *box)
{
	if (box->ent != NULL)
	{
		if (box->ent->n == 'P' || box->ent->n == 'C'
			|| box->ent->n == 'E' || box->ent->n == 'M')
			return (1);
		return (0);
	}
	return (1);
}

/**
 * Initialize the user interface and textures.
*/
int	init_ui_bonus(t_game *game, t_entity *ents)
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
	game->textures = init_textures_bonus(game);
	if (game->textures == NULL)
	{
		free_map(game->map);
		print_error("Malloc error in init_texture()");
	}
	return (1);
}

/**
 * Give each entities it's own sprite.
*/
void	build_entities_bonus(t_game *g)
{
	t_entity	*ent;

	ent = g->entities;
	while (ent != NULL)
	{
		if (ent->n == 'C')
			ent->sprite = mlx_texture_to_image(g->mlx, g->textures[3]);
		else if (ent->n == 'P')
			ent->sprite = mlx_texture_to_image(g->mlx, g->textures[2]);
		else if (ent->n == 'E')
			ent->sprite = mlx_texture_to_image(g->mlx, g->textures[4]);
		else if (ent->n == 'M')
			init_anim(ent, g);
		else
			print_error("Undefined error in parsing.");
		if (ent->sprite == NULL)
			print_error("MLX failed to do it's job in build_entities()");
		ent = ent->next;
	}
}
