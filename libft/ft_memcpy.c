/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:45:22 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:45:23 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Copies memory area
 * 
 * @param dst 
 * @param src 
 * @param n 
 * @return void* 
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dst1;
	const char	*src1;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst1 = dst;
	src1 = src;
	i = 0;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}
