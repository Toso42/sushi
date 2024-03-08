/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:38:17 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:53:46 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare if len of two parameters is equal.
 * If not equal, the difference in lenght is returned;
 * if equal in lenght, the difference in value of first
 * different char is returned.
 * 
 * @param x 
 * @param y 
 * @return int 
 */

int	ft_strcmp_precision(const char *x, const char *y)
{
	int	lendifference;
	int	cursor;

	cursor = -1;
	lendifference = (ft_strlen(x) - ft_strlen(y));
	if (lendifference)
		return (lendifference);
	while (x[++cursor])
	{
		if (x[cursor] != y [cursor])
			return (x[cursor] - y[cursor]);
	}
	return (0);
}
