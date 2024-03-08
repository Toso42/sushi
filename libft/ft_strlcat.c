/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:47:04 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:47:06 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief appends string src to the end of dst.  It will append at most dstsize 
 * - strlen(dst) - 1 characters.  It willthen NUL-terminate, unless dstsize is 
 * 0 or the original dst string was longer than dstsize (in practice this should 
 * not happen as it means that either dstsize is incorrect or that dst is not a 
 * proper string).
 * 
 * @param dst destination
 * @param src source to append at the end of src
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}
