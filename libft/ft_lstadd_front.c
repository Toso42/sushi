/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:43:50 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:43:51 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the beginning of the list.
 * 
 * @param lst node head
 * @param new node to append as new head
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst != NULL)
		new->next = (*lst);
	(*lst) = new;
}
