/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:42:44 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:42:45 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Takes a char** and copy it with malloc;
 * 
 * @param str 
 * @return Mallocate copy of **str in a char** called new_str;
 */

char	**ft_sarcopy(char **str)
{
	int		j;
	int		i;
	char	**new_str;

	i = -1;
	j = ft_sarsize(str);
	new_str = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new_str)
		return (NULL);
	if (j != 0)
	{
		while (++i < j)
			new_str[i] = ft_strdup(str[i]);
		new_str[i] = NULL;
	}
	return (new_str);
}
