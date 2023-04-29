/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:46:36 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/22 19:19:51 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Free an array of string, then return NULL.
*/
char	**free_tab_str(char **tab)
{
	int	ct;

	ct = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[ct] != NULL)
		free(tab[ct++]);
	free(tab);
	return (NULL);
}

/**
 * Free everything we used then exit the program with an error message.
*/
void	free_append_tab(char **tab, char *s, char **new_tab)
{
	if (tab != NULL)
		free_tab_str(tab);
	if (s != NULL)
		free(s);
	if (new_tab != NULL)
		free_tab_str(new_tab);
	print_error("Malloc failed");
}

/**
 * Move tab and s in a new array then return it.
 * If tab is NULL, create a new array of string holding s.
*/
char	**ft_append_tab(char **tab, char *s)
{
	char	**new_tab;
	int		size;

	if (tab == NULL)
		size = 1;
	else
		size = 2;
	while (tab != NULL && tab[size - 1] != NULL)
		size++;
	new_tab = malloc((size + 1) * sizeof(char *));
	if (new_tab == NULL)
		free_append_tab(tab, s, NULL);
	size = 0;
	while (tab != NULL && tab[size] != NULL)
	{
		new_tab[size] = tab[size];
		size++;
	}
	new_tab[size++] = ft_strtrim(s, "\n");
	if (new_tab[size - 1] == NULL)
		free_append_tab(tab, s, new_tab);
	new_tab[size] = NULL;
	free(tab);
	free(s);
	return (new_tab);
}

/**
 * Verify whether the file exists and has a good name, then try to open it.
 * Return the corresponding file descriptor or exit if an error occured.
*/
int	ft_verify_file(char *file)
{
	int	fd;
	int	last;

	if (file == NULL || ft_strlen(file) < 5)
		print_error("File name too short or intolerable");
	last = ft_strlen(file) - 1;
	if (file[last] != 'r' || file[last - 1] != 'e'
		|| file[last - 2] != 'b' || file[last - 3] != '.')
		print_error("Bad extension for the file name");
	errno = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error(file);
	return (fd);
}
