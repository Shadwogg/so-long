/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:36:21 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/26 18:28:17 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Add at the end of the list the new node created from the coordinates.
*/
void	add_back(t_node **visited, int x, int y)
{
	t_node	*new;
	t_node	*cur;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return ;
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (*visited == NULL)
	{
		*visited = new;
		return ;
	}
	cur = *visited;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

/**
 * Check if the current node we try to explore is already explored.
*/
int	is_visited(t_node *visited, int x, int y)
{
	while (visited != NULL)
	{
		if (visited->x == x && visited->y == y)
			return (1);
		visited = visited->next;
	}
	return (0);
}

/**
 * Check if we can reach the exit after taking every coin.
*/
int	final_check(t_case ***map, t_node *visited, int nb_coin)
{
	if (nb_coin == 0)
	{
		while (visited)
		{
			if (map[visited->y][visited->x]->ent)
			{
				if (map[visited->y][visited->x]->ent->n == 'E')
					return (1);
			}
			visited = visited->next;
		}
	}
	return (0);
}

/**
 * The flood algorithm "fills" every case in the board from the starting point
 * to see if there's a way between multiples point.
*/
void	ft_flood(t_case ***map, t_node **visited, int x, int y)
{
	if (!is_visited(*visited, x, y))
		add_back(visited, x, y);
	if (!is_visited(*visited, x, y))
	{
		free_nodes(*visited);
		*visited = NULL;
		return ;
	}
	if (!map[y - 1][x]->is_wall && !is_visited(*visited, x, y - 1))
		ft_flood(map, visited, x, y - 1);
	if (!map[y + 1][x]->is_wall && !is_visited(*visited, x, y + 1))
		ft_flood(map, visited, x, y + 1);
	if (!map[y][x - 1]->is_wall && !is_visited(*visited, x - 1, y))
		ft_flood(map, visited, x - 1, y);
	if (!map[y][x + 1]->is_wall && !is_visited(*visited, x + 1, y))
		ft_flood(map, visited, x + 1, y);
}

/**
 * Use the flood algorithm to check if every coin and the exit
 * are reachable by the player.
*/
int	map_is_possible(t_case ***map, t_entity *player, int nb_coin)
{
	t_node	*visited;
	t_node	*cur;
	int		res;

	visited = NULL;
	ft_flood(map, &visited, player->coo[0] / 64, player->coo[1] / 64);
	if (visited == NULL)
	{
		free_map(map);
		print_error("Malloc failed during the flood algorithm");
	}
	cur = visited;
	while (cur != NULL)
	{
		if (map[cur->y][cur->x]->ent && map[cur->y][cur->x]->ent->n == 'C')
			nb_coin -= 1;
		cur = cur->next;
	}
	res = final_check(map, visited, nb_coin);
	free_nodes(visited);
	return (res);
}
