/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:12:15 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 23:15:54 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long_bonus.h"

void	set_next_frame(t_entity *ent)
{
	if (ent->sprite->enabled == 1)
	{
		ent->sprite->enabled = 0;
		ent->sprite2->enabled = 1;
	}
	else if (ent->sprite2->enabled == 1)
	{
		ent->sprite2->enabled = 0;
		ent->sprite3->enabled = 1;
	}
	else if (ent->sprite3->enabled == 1)
	{
		ent->sprite3->enabled = 0;
		ent->sprite4->enabled = 1;
	}
	else if (ent->sprite4->enabled == 1)
	{
		ent->sprite4->enabled = 0;
		ent->sprite->enabled = 1;
	}
}

void	anime_sprite(t_game *g)
{
	static double	delta_time_cum;
	t_entity		*cur;

	cur = g->entities;
	delta_time_cum += g->mlx->delta_time;
	if (delta_time_cum > 1)
	{
		while (cur != NULL)
		{
			if (cur->n == 'M')
				set_next_frame(cur);
			cur = cur->next;
		}
		delta_time_cum -= 1;
	}
}

void	prepare_animation(t_game *game, int o_x, int o_y)
{
	t_entity	*ent;

	ent = game->entities;
	while (ent != NULL)
	{
		if (ent->n == 'M')
		{
			mlx_image_to_window(game->mlx, ent->sprite2,
				ent->coo[0] + o_x, ent->coo[1] + o_y);
			ent->sprite2->enabled = 0;
			mlx_image_to_window(game->mlx, ent->sprite3,
				ent->coo[0] + o_x, ent->coo[1] + o_y);
			ent->sprite3->enabled = 0;
			mlx_image_to_window(game->mlx, ent->sprite4,
				ent->coo[0] + o_x, ent->coo[1] + o_y);
			ent->sprite4->enabled = 0;
		}
		ent = ent->next;
	}
}

void	rotate_img(mlx_image_t *dst, mlx_image_t *src)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < src->width)
	{
		y = 0;
		while (y < src->height)
		{
			mlx_put_pixel(dst, -y + src->width - 1, x,
				get_pixel(src, x * 4, y * 4));
			y++;
		}
		x++;
	}
}

void	init_anim(t_entity *ent, t_game *g)
{
	ent->sprite = mlx_texture_to_image(g->mlx, g->textures[5]);
	ent->sprite2 = mlx_texture_to_image(g->mlx, g->textures[5]);
	rotate_img(ent->sprite2, ent->sprite);
	ent->sprite3 = mlx_texture_to_image(g->mlx, g->textures[5]);
	rotate_img(ent->sprite3, ent->sprite2);
	ent->sprite4 = mlx_texture_to_image(g->mlx, g->textures[5]);
	rotate_img(ent->sprite4, ent->sprite3);
}
