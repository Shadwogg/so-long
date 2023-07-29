/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:38:09 by ggiboury          #+#    #+#             */
/*   Updated: 2023/07/29 22:42:10 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Return the size of the string we must create.
*/
int	itos_get_len(int x)
{
	int	size;

	if (x == 0)
		return (1);
	size = 0;
	while (x != 0)
	{
		size++;
		if (x >= 0 && x < 10)
			break ;
		x /= 10;
	}
	return (size);
}

/**
 * Like itoa, but with a better name.
*/
char	*ft_itos(unsigned int x)
{
	char	*str;
	int		ct;

	ct = itos_get_len(x);
	str = malloc((ct + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[ct--] = 0;
	if (x == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (x != 0)
	{
		if (x >= 0 && x < 10)
			str[ct] = x + 48;
		else
			str[ct] = x % 10 + 48;
		x /= 10;
		ct--;
	}
	return (str);
}
