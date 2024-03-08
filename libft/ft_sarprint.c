/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:37 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:28:38 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * @brief prints a strings array wholly, surrounded by limitator characters, 
 * printing a \n after each string
 * 
 * @param **sar 
 * @return ret sum of chars printed
 */

int	ft_sarprint(char **sar)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (!sar || !sar[0])
		return (0);
	ft_printf("---SPLITTED ARGS---\n");
	while (sar[++i] && sar[i] != 0)
	{
		ret += ft_printf("\"%s\"\n", sar[i]);
	}
	ft_printf("-----########-----\n");
	return (ret);
}
