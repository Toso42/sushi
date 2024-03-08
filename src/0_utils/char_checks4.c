/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:34 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 12:05:12 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_open_parenthesis(char c)
{
	if (c == '(')
		return (1);
	return (0);
}

int	is_close_parenthesis(char c)
{
	if (c == ')')
		return (1);
	return (0);
}
