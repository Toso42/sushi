/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:48:20 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:53:19 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief copies up to dstsize - 1 characters from the string src to dst, 
 * NUL-terminating the result if dstsize is not 0.
 * 
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_printd(0, " dest: {%s} src {%s} destsize: {%d}\n", dst, src, dstsize);
	while (src[i] != '\0')
	{
		i++;
	}
	if (dstsize != 0)
	{
		while (src[j] != '\0' && j < (dstsize - 1))
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (i);
}
