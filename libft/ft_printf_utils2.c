/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:40:45 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/04/23 16:50:38 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printftypestring(va_list args, char *ss, int sum)
{
	ss = va_arg(args, char *);
	if (ss == NULL)
		sum = ft_putstring("(null)", sum);
	else if (ss != NULL)
		sum = ft_putstring(ss, sum);
}
