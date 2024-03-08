/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_precision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:38:42 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:55:10 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strnstr() function locates the first occurrence of the
 * null-terminated string needle in the string haystack, where not 
 * more than len characters are searched. Characters that appear 
 * after a ‘\0’ character are not searched. 
 * 
 * @param haystack 
 * @param needle 
 * @param len 
 * @param terminator 
 * @return char* If needle is an empty string, NULL is returned;
 * if needle occurs nowhere in haystack, NULL is returned;
 * otherwise a pointer to the first character of the first occurrence
 * of needle is returned.
 */
char	*ft_strnstr_precision(const char *haystack, const char *needle, \
				size_t len, char terminator)
{
	size_t	i;
	size_t	j;
	char	*src;
	char	*tf;

	i = 0;
	j = 0;
	src = (char *)haystack;
	tf = (char *)needle;
	if (*needle == '\0')
		return (NULL);
	while (src[i] != '\0' && i < len)
	{
		while (i + j < len && tf[j] != '\0' && src[i + j] == tf[j])
		{
			j++;
			if (tf[j] == '\0'
				&& (src[i + j] == 0 || src[i + j] == terminator))
				return (src + i);
		}
		j = 0;
		i++;
	}
	return (0);
}
