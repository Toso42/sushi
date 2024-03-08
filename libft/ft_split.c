/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:46:25 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 15:13:11 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_args(char *string, char separator)
{
	int	cursor;
	int	sep_counter;

	cursor = -1;
	sep_counter = 1;
	while (string[++cursor])
	{
		if (string[cursor] == separator)
		{
			sep_counter++;
		}
	}
	return (sep_counter);
}

char	**create_arguments(char *string, char separator, char **splitted_args)
{
	int	cursor;
	int	arg_counter;
	int	starting_point;

	cursor = -1;
	arg_counter = 0;
	starting_point = 0;
	while (string[++cursor])
	{
		if (string[cursor] == separator)
		{
			splitted_args[arg_counter] = ft_substr(string, starting_point, \
								(cursor - starting_point));
			starting_point = cursor + 1;
			arg_counter++;
		}
	}
	if (string[cursor - 1] != separator)
	{
		splitted_args[arg_counter] = ft_substr(string, starting_point, \
								(cursor - starting_point));
		arg_counter++;
	}
	splitted_args[arg_counter] = NULL;
	return (splitted_args);
}

/**
 * @brief Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
 * 
 * @param s string to split
 * @param c char splitter
 * @return char** array of splitted arguments
 */
char	**ft_split(const char *s, char c)
{
	char	**splitted_args;

	if (!s)
		return (NULL);
	splitted_args = (char **) malloc \
		((count_args((char *)s, c) + 1) * sizeof(char *));
	if (!splitted_args)
		return (NULL);
	create_arguments((char *)s, c, splitted_args);
	return (splitted_args);
}
