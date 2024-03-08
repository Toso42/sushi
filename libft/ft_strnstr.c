/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:49:02 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/29 11:06:20 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strnstr() function locates the first occurrence of the
 * null-terminated string needle in the string haystack,
 * where not more than len characters are searched.
 * Characters that appear after a ‘\0’ character are not searched.
 * Since the strnstr() function is a FreeBSD specific API,
 * it should only be used when portability is not a concern.
 * 
 * @param haystack 
 * @param needle 
 * @param len 
 * @return char* If needle is an empty string, haystack is returned;
 * if needle occurs nowhere in haystack, NULL is returned; otherwise
 * a pointer to the first character of the first occurrence of 
 * needle is returned.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
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
		return (src);
	while (src[i] != '\0' && i < len)
	{
		while (i + j < len && tf[j] != '\0' && src[i + j] == tf[j])
		{
			j++;
			if (tf[j] == '\0')
				return (src + i);
		}
		j = 0;
		i++;
	}
	return (0);
}
