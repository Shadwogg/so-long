/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:10:56 by ggiboury          #+#    #+#             */
/*   Updated: 2023/05/02 20:02:33 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Create and return a new entity.
*/
t_entity	*new_entity(char c, int x, int y)
{
	t_entity	*ent;

	ent = malloc(sizeof(t_entity));
	if (ent == NULL)
	{
		ft_printf("Error : malloc failed in new_entity");
		return (NULL);
	}
	ent->coo[0] = x * SIZE_IMG;
	ent->coo[1] = y * SIZE_IMG;
	ent->life = 1;
	ent->n = c;
	ent->next = NULL;
	return (ent);
}

/**
 * Initialize a case of the board.
*/
t_case	*init_case(char c, int x, int y)
{
	t_case	*box;

	box = malloc(sizeof(t_case));
	if (box == NULL)
		return (NULL);
	box->is_wall = 0;
	box->ent = NULL;
	box->sprite = NULL;
	if (c == '0' || c == '1')
		box->is_wall = !(c % 2 == 0);
	else
	{
		box->ent = new_entity(c, x, y);
		if (box->ent == NULL)
			return (NULL);
	}
	return (box);
}

/**
 * Free the map and print error.
*/
void	malloc_error_map(t_case ***map, int y, char **input)
{
	int	x;

	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != NULL)
		{
			if (map[y][x]->ent != NULL)
				free(map[y][x]->ent);
			free(map[y][x]);
		}
		free(map[y]);
	}
	free(map);
	free_tab_str(input);
	print_error("Malloc error while parsing the map");
}

/**
 * Free the boxes used when there is a box invalid.
*/
void	free_boxes(t_case ***map, int x, int b, char **input)
{
	int	ct;
	int	ct2;

	free_tab_str(input);
	ct = -1;
	while (map[++ct] != NULL)
	{
		ct2 = -1;
		while (++ct2 < x || map[ct][ct2] != NULL)
		{
			if (map[ct][ct2]->ent != NULL)
				free(map[ct][ct2]->ent);
			free(map[ct][ct2]);
		}
		free(map[ct]);
	}
	if (b)
		print_error("Malloc error.");
	print_error("Unknown character encouter during the parsing.");
}

/**
 * Initialize the map.
*/
t_case	***init_map(char **input, int y, int x)
{
	t_case	***map;
	int		ct;

	if (input == NULL || *input == NULL)
		return (NULL);
	map = malloc((y + 1) * sizeof(t_case *));
	if (map == NULL)
		free_print_error(input, "Malloc error");
	map[y--] = NULL;
	while (y >= 0)
	{
		map[y] = malloc((x + 1) * sizeof(t_case));
		if (map[y] == NULL)
			malloc_error_map(map, y, input);
		ct = -1;
		while (++ct < x)
		{
			map[y][ct] = init_case(input[y][ct], ct, y);
			if (map[y][ct] == NULL || !case_is_valid(map[y][ct]))
				free_boxes(map + y, ct, map[y][ct] == NULL, input);
		}
		map[y--][x] = NULL;
	}
	free_tab_str(input);
	return (map);
}

/**
 * Verify that the map is rectangular and parse it.
*/
t_case	***ft_parse(int fd)
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
	return (init_map(input, nb_line, size));
}
