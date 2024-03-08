/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:02:24 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 17:07:48 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief it shall eventually be updated to take a **tofree, to se to NULL
 * the pointer 0 page. Still safe to use for pointers inside structs.
 * 
 * @param tofree 
 */
void	ft_free(char *tofree)
{
	if (tofree)
	{
		free(tofree);
			tofree = NULL;
	}
}
