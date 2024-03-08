/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoicheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:09:27 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 11:13:05 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Check if str consists only of numeric characters.
 * 
 * @param str 
 * @return int True or False
 */
int	ft_atoicheck(char *str)
{
	int	cursor;

	cursor = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		cursor++;
	while (str[cursor])
	{
		if (str[cursor] < '0' || str[cursor] > '9')
			return (0);
		cursor++;
	}
	return (1);
}
