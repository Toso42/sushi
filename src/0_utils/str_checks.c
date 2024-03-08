/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:20:11 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 17:23:35 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_valid_redirection(char *arg)
{
	if (!ft_strcmp_precision(arg, ">")
		|| !ft_strcmp_precision(arg, ">>")
		|| !ft_strcmp_precision(arg, "<")
		|| !ft_strcmp_precision(arg, "<<"))
		return (1);
	return (0);
}

int	is_valid_operator(char *arg)
{
	if (!ft_strcmp_precision(arg, "&")
		|| !ft_strcmp_precision(arg, "&&")
		|| !ft_strcmp_precision(arg, "|")
		|| !ft_strcmp_precision(arg, "||"))
		return (1);
	return (0);
}

int	is_valid_pipe(char *arg)
{
	if (!ft_strcmp_precision(arg, "|"))
		return (1);
	return (0);
}

int	is_command(char *token)
{
	if (!token)
		return (1);
	if (token
		&& !is_parenthesis(token[0])
		&& !is_valid_operator(token)
		&& !is_valid_pipe(token)
		&& !is_valid_redirection(token))
		return (1);
	return (0);
}

int	is_logical_operator(char *arg)
{
	if (!ft_strcmp_precision(arg, "&&")
		|| !ft_strcmp_precision(arg, "||"))
	{
		return (1);
	}
	return (0);
}
