/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strintertrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:43:02 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:43:03 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief mallocates a new line, copying everything from
 * (*totrim) excluding all (c) occurrences.
 * It DOES FREE the original line, returning the new line.
 * 
 * @param totrim 
 * @param c 
 * @return char* 
 */

int	count_c(char *totrim, char c)
{
	int	i;
	int	cursor;

	i = 0;
	cursor = -1;
	while (totrim[++cursor])
		if (totrim[cursor] == c)
			i++;
	return (i);
}

char	*ft_strintertrim(char *totrim, char c)
{
	int		c_counter;
	int		cursor;
	int		nl_cursor;
	char	*newline;

	c_counter = count_c(totrim, c);
	cursor = -1;
	nl_cursor = -1;
	if (!totrim)
		return (NULL);
	if (!c)
		return (totrim);
	newline = (char *)malloc(sizeof(char *) * \
		(ft_strlen(totrim) - c_counter) + 1);
	if (!newline)
		return (totrim);
	cursor = -1;
	while (totrim[++cursor])
		if (totrim[cursor] != c)
			newline[++nl_cursor] = totrim[cursor];
	newline[++nl_cursor] = 0;
	if (totrim)
		free(totrim);
	return (newline);
}
