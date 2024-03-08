/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:42:37 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:42:38 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief write zeroes to a byte string
 * 
 * @param void *s
 * @param size_t n 
 */
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*cp;

	if (n == 0)
		return ;
	i = -1;
	cp = s;
	while (++i < n)
		cp[i] = '\0';
}
