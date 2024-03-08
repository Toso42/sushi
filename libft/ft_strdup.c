/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:46:38 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:54:23 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strdup() function allocates sufficient memory for a copy of the 
 * string s1, does the copy, and returns a pointer to it.  The pointer may 
 * subsequently be used as an argument to the function free(3).
 * 
 * @param s1 
 * @return char* 
 */
char	*ft_strdup(const char *s1)
{
	int		lenght;
	char	*dest;

	lenght = ft_strlen(s1);
	dest = (char *) malloc ((lenght + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (!lenght)
		dest[0] = 0;
	else
		ft_memmove(dest, s1, lenght);
	dest[lenght] = '\0';
	return (dest);
}
