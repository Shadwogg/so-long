/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:25:11 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/29 18:47:37 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "so_long_bonus.h"

/**
 * Use the flood algorithm to check if every coin and the exit
 * are reachable by the player.
*/
int	map_is_possible_bonus(t_case ***map, t_entity *p, int nb_coin)
{
	t_node	*visited;
	t_node	*cur;
	int		res;

	visited = NULL;
	print_map(map);
	ft_flood_bonus(map, &visited, p->coo[0] / 64, p->coo[1] / 64);
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

/**
 * Verify that the map is rectangular and parse it.
*/
t_case	***ft_parse_bonus(int fd)
{
	char	**input;
	char	*line;
	int		size;
	int		nb_line;

	input = NULL;
	size = -2;
	nb_line = 0;
	while (size != 0)
	{
		line = get_next_line(fd);
		if (line == 0 || line[0] == '\n')
			break ;
		input = ft_append_tab(input, line);
		if (input == NULL)
			print_error("Malloc failed");
		if (size != -2 && size != (int) ft_strlen(input[nb_line]))
			free_print_error(input, "Map must be rectangular");
		size = ft_strlen(input[nb_line]);
		nb_line++;
	}
	return (init_map_bonus(input, nb_line, size));
}

/**
 * Initialize the map.
*/
t_case	***init_map_bonus(char **input, int y, int x)
{
	t_case	***map;
	int		ct;

	if (input == NULL || *input == NULL)
		return (NULL);
	map = malloc((y + 1) * sizeof(t_case **));
	if (map == NULL)
		free_print_error(input, "Malloc error");
	map[y--] = NULL;
	while (y >= 0)
	{
		map[y] = malloc((x + 1) * sizeof(t_case **));
		if (map[y] == NULL)
			malloc_error_map(map, x, y + 1);
		ct = -1;
		while (++ct < x)
		{
			map[y][ct] = init_case(input[y][ct], ct, y);
			if (map[y][ct] == NULL || !case_is_valid_bonus(map[y][ct]))
				malloc_error_map(map, x, y);
		}
		map[y--][x] = NULL;
	}
	free_tab_str(input);
	return (map);
}
