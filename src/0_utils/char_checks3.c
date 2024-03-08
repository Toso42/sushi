/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:31 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 11:57:18 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_an_acceptable_char(char c)
{
	if (!ft_isalnum(c) && c != '/' \
			&& c != '@' && c != '?' \
			&& c != ',' && c != '.' \
			&& c != '*' && c != '%' \
			&& c != ' ' && c != '=' \
			&& c != ':' && c != '-' \
			&& c != '+')
	{
		return (0);
	}
	return (1);
}

int	is_regular_separator(char c)
{
	if (is_space(c))
		return (1);
	return (0);
}

int	is_parenthesis(char c)
{
	if ((c == '(')
		|| c == ')')
		return (1);
	return (0);
}

int	is_and(char c)
{
	if (c == '&')
		return (1);
	return (0);
}

int	is_or(char c)
{
	if (c == '|')
		return (1);
	return (0);
}
