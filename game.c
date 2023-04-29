/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:50:19 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/29 17:48:03 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Use each image to build a view for the game depending on the start position.
*/
void	render(t_game *g, int o_x, int o_y)
{
	t_entity	*ent;
	int			ct;
	int			ct2;

	ct = -1;
	while (g->map[++ct])
	{
		ct2 = -1;
		while (g->map[ct][++ct2])
			mlx_image_to_window(g->mlx, g->map[ct][ct2]->sprite,
				ct2 * SIZE_IMG + o_x, ct * SIZE_IMG + o_y);
	}
	ent = g->entities;
	while (ent != NULL)
	{
		mlx_image_to_window(g->mlx, ent->sprite,
			ent->coo[0] + o_x, ent->coo[1] + o_y);
		if (ent->n == 'E')
			ent->sprite->instances->enabled = false;
		ent = ent->next;
	}
}

/**
 * Render the panel for the bonus.
*/
void	render_panel(t_game *g)
{
	char	*str;

	g->str[0] = mlx_put_string(g->mlx, "Moves : ", 0, 0);
	g->str[1] = mlx_put_string(g->mlx, "Items left : ", 0, 20);
	str = ft_itos(0);
	g->ct_img = mlx_put_string(g->mlx, str, 30, 0);
	free(str);
	str = ft_itos(g->ct_items);
	g->ct2_img = mlx_put_string(g->mlx, str, 125, 20);
	free(str);
}

/**
 * Give each entities it's own sprite.
*/
void	build_entities(t_game *g)
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
		else
			print_error("Undefined error in parsing.");
		if (ent->sprite == NULL)
			print_error("MLX failed to do it's job in build_entities()");
		ent = ent->next;
	}
}
