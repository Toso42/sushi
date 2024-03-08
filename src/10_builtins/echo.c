/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:25:04 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:12 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_command(char **str)
{
	int	cursor;

	cursor = 0;
	while (str[cursor + 1] && !ft_strncmp(str[cursor + 1], "-n", 3))
		cursor++;
	while (str[++cursor])
	{
		ft_printf("%s", str[cursor]);
		if (str[cursor + 1])
			ft_printf(" ");
	}
	if (!str[1] || ft_strncmp(str[1], "-n", 3))
		ft_printf("\n");
	ft_printd(0, "echo exiting\n");
	return (error_handler(0, NULL, DO_NOT_RESET));
}
