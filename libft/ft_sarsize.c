/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:44 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/10/24 16:38:47 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief misurates the number of strings in a strings array
 * 
 * @param tocount 
 * @return int 
 */
int	ft_sarsize(char **tocount)
{
	int	j;

	j = -1;
	if (!tocount)
		return (0);
	while (tocount[++j])
		;
	return (j);
}
