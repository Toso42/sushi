/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:15:13 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/04/23 17:06:49 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_printbits(int bits, int toprint)
{
	int	sum;

	sum = bits;
	while (bits-- > 0)
	{
		if (toprint >> bits & 1)
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	return (sum);
}
