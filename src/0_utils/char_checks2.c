/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:27 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 11:32:00 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_symbol_separator(char c)
{
	if ((c >= 33 && c <= 47)
		|| (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94)
		|| (c == 96)
		|| (c >= 123 && c <= 126)
		|| (is_eof(c))
		|| (is_space(c)))
		return (1);
	return (0);
}

int	is_var_terminator(char c)
{
	if (is_symbol_separator(c))
		return (1);
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if ((c == '<')
		|| c == '>')
	{
		return (1);
	}
	return (0);
}

int	is_operator(char c)
{
	if ((c == '&')
		|| c == '|')
	{
		return (1);
	}
	return (0);
}
