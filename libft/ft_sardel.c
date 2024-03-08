/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sardel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:41:14 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 16:42:19 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a copy of (**sar) withouth the (todel) element. FREES the old 
 * (**sar)
 * 
 * @param sar 
 * @param todel 
 * return **new_sar
 */
char	**ft_sardel(char **sar, int todel)
{
	char	**new_sar;
	int		oldsar_size;
	int		counter;
	int		new_sar_counter;

	counter = -1;
	new_sar_counter = -1;
	oldsar_size = ft_sarsize(sar);
	new_sar = (char **)malloc(sizeof(char *) * ((oldsar_size + 1) - 1));
	while (++counter < oldsar_size)
	{
		if (counter != todel)
		{
			new_sar[++new_sar_counter] = ft_strdup(sar[counter]);
			ft_printd(0, "sardel, copying {%s}, arg %d\n",
				sar[counter], new_sar_counter);
		}
	}
	ft_printd(0, "sardel, setting arg %d to NULL\n", (new_sar_counter + 1));
	new_sar[++new_sar_counter] = NULL;
	ft_sarfree(sar, ft_sarsize(sar));
	return (new_sar);
}
