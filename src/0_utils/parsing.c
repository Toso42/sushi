/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:18:24 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 11:35:32 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

int	is_valid_command(char *cmd)
{
	char	**split;

	if (!cmd)
		return (0);
	split = ft_split(cmd, ' ');
	if (ft_sarsize(split) > 0)
	{
		free(split);
		return (1);
	}
	return (0);
}
