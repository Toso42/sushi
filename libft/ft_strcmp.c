/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:06:53 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 11:09:00 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare str with to_compare.
 * 
 * @param str 
 * @param to_compare 
 * @return int Difference.
 */
int	ft_strcmp(const char *str, const char *to_compare)
{
	while (*str)
	{
		if (*str != *to_compare)
			break ;
		str++;
		to_compare++;
	}
	return (*(const unsigned char *)str - *(const unsigned char *)to_compare);
}
