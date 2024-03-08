/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tdi-leo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:15 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/02 16:55:15 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief mallocates a new string array, with (toadd) string as first and only
 * argument. It DOES NOT free (toadd) string.
 * 
 * @param toadd 
 * @return char** joined_array
 */
static char	**new_sar(char *toadd)
{
	char	**joined_array;

	if (!toadd)
		return (NULL);
	joined_array = (char **)malloc(sizeof(char *) * 2);
	if (!joined_array)
		return (NULL);
	if (!ft_strlen(toadd))
		joined_array[0] = ft_strdup("");
	else
	{
		joined_array[0] = ft_substr(toadd, 0, ft_strlen(toadd));
	}
	joined_array[1] = NULL;
	return (joined_array);
}

/**
 * @brief create a new strings array, copying (base) and adding (toadd) 
 * string at the end. It then frees up base (but not toadd string).
 * 
 * @param **base strings array
 * @param toadd string
 * @return char** 
 */
char	**ft_saradd_back(char **base, char *toadd)
{
	int		i;
	char	**joined_array;

	i = -1;
	if (!base && !toadd)
		return (NULL);
	if (base && !toadd)
		return (base);
	if (!toadd)
		return (new_sar(NULL));
	if (!base)
		joined_array = new_sar(toadd);
	else
	{
		joined_array = (char **)malloc(sizeof(char *) * (ft_sarsize(base) + 2));
		if (!joined_array)
			return (NULL);
		while (base[++i])
			joined_array[i] = ft_substr(base[i], 0, ft_strlen(base[i]));
		joined_array[i] = ft_substr(toadd, 0, ft_strlen(toadd));
		joined_array[++i] = 0;
	}
	if (base)
		ft_sarfree(base, ft_sarsize(base));
	return (joined_array);
}
