/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:25 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/21 21:50:17 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief frees string array, freeing each element and then
 * freeing the array itself.
 * 
 * @param sar 
 * @param y 
 */

/*&& ft_strlen(sar[x])) riga 34*/

void	ft_sarfree(char **sar, int y)
{
	int	x;

	x = -1;
	if (!sar)
		return ;
	while (++x < y)
	{
		if (sar[x])
		{
			free(sar[x]);
			sar[x] = NULL;
		}
	}
	if (sar)
	{
		free(sar);
		sar = NULL;
	}
}
