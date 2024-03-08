/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:44:51 by kzak              #+#    #+#             */
/*   Updated: 2022/12/30 11:45:07 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_valid_operator2(char *arg)
{
	if (!ft_strcmp_precision(arg, "&")
		|| !ft_strcmp_precision(arg, "&&")
		|| !ft_strcmp_precision(arg, "|")
		|| !ft_strcmp_precision(arg, "||")
		|| !is_valid_redirection(arg))
		return (1);
	return (0);
}
