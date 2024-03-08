/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:20 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 11:56:38 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

/**
 * $
 */
int	is_var(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

/**
 * '
 */
int	is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

/**
 * "
 */
int	is_dquote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

/**
* all kind of spaces
*/
int	is_space(char c)
{
	if (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	is_eof(char c)
{
	if (c == '\0')
		return (1);
	return (0);
}
