/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:36:19 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/26 20:32:36 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Print an error to the prompt.
*/
int	print_error(char *s)
{
	if (errno == 0)
		ft_printf("%s\n", s);
	else
		perror(s);
	exit(EXIT_SUCCESS);
}

/**
 * Print the list of all entities.
*/
void	print_entities(t_entity *ent)
{
	if (ent == NULL)
		ft_printf("No entities.");
	else
	{
		while (ent != NULL)
		{
			ft_printf("%c ", ent->n);
			ent = ent->next;
		}
	}
	ft_printf("\n");
}

/**
 * Print the map in the console.
*/
void	print_map(t_case ***map)
{
	int	ct;
	int	ct2;

	ct = -1;
	while (map[++ct] != NULL)
	{
		ct2 = -1;
		while (map[ct][++ct2])
		{
			if (map[ct][ct2]->is_wall)
				ft_printf("1");
			else if (map[ct][ct2]->ent != NULL)
				ft_printf("%c", map[ct][ct2]->ent->n);
			else
				ft_printf(" ");
		}
		ft_printf("\n");
	}
}

/**
 * Print the nodes used in ft_flood().
*/
void	print_nodes(t_node *v)
{
	while (v != NULL)
	{
		ft_printf("[%d, %d]->", v->x, v->y);
		v = v->next;
	}
	ft_printf("NULL\n");
}

void	print_on_mov(int moves)
{
	if (moves % 8 == 0)
		ft_printf("Move : %d\n", moves / 8);
}
