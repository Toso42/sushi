/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:48:56 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 22:16:58 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief searches inside haystack *s1, if there's needle *s2, searching
 * up to n len chars into haystack
 * 
 * @param s1 haystack
 * @param s2 needle
 * @param n lenght
 * @return int 
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n--)
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
	}
	return (0);
}
