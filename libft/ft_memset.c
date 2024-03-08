/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:45:42 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:45:43 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief fill a byte string with a byte value
 * 
 * @param *b void string
 * @param c int value
 * @param len size_t
 * @return void* 
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	l;
	char			*x;

	x = b;
	l = (unsigned char)c;
	while (len--)
		*x++ = l;
	return (b);
}
