/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:46:32 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:46:33 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * returns positive if a char is found.
 * 
*/
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (i--)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}
