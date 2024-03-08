/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:22:01 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:27:27 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd_command(void)
{
	char	actual_path[PATH_MAX];

	ft_printf("%s\n", getcwd(actual_path, sizeof(actual_path)));
	return (error_handler(0, NULL, DO_NOT_RESET));
}
