/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:39:01 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 17:01:31 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’. IT DOES free (s1) and (s2).
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*joined_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
	{
		ft_free(s1);
		ft_free(s2);
		return (NULL);
	}
	joined_str = (char *) malloc (((sizeof(char))
				* (ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (joined_str == NULL)
		return (NULL);
	while (s1[j] != '\0')
		joined_str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		joined_str[i++] = s2[j++];
	joined_str[i] = '\0';
	ft_free(s1);
	ft_free(s2);
	return (joined_str);
}
