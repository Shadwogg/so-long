/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:03:58 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 23:03:33 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Free the board.
*/
void	free_map(t_case ***map)
{
	int	ct;
	int	ct2;

	ct = -1;
	while (map[++ct] != NULL)
	{
		ct2 = -1;
		while (map[ct][++ct2] != NULL)
		{
			if (map[ct][ct2]->ent != NULL)
				free(map[ct][ct2]->ent);
			free(map[ct][ct2]);
		}
	}
}

/**
 * Free the list of nodes I used for ft_flood().
*/
void	free_nodes(t_node *v)
{
	t_node	*cur;

	while (v != NULL)
	{
		cur = v;
		v = v->next;
		free(cur);
	}
}

/**
 * Free the game.
*/
void	free_game(t_game g)
{
	int	ct;

	ct = 0;
	free_map(g.map);
	while ((g.textures[ct]) != NULL)
	{
		mlx_delete_texture(g.textures[ct]);
		ct++;
	}
	free(g.textures);
}

/**
 * Free every entities used in the program.
*/
void	free_entities(t_game g)
{
	t_entity	*cur;

	cur = g.entities;
	while (cur != NULL)
	{
		cur = g.entities->next;
		free(g.entities);
		g.entities = cur;
	}
}

/**
 * Free str, print s and exit the program.
*/
void	free_print_error(char **str, char *s)
{
	free_tab_str(str);
	print_error(s);
}
