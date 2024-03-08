/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:23:23 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:23 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_command(t_shell *shell)
{
	char	*error_string;

	if (shell->is_terminal_process == 0)
		ft_printfd(STDERR_FILENO, "exit \n");
	if (shell->final_arguments[1] && shell->final_arguments[2])
	{
		return (error_handler(1, ft_strdup("sushi: exit: too many arguments"),
				RESET_PRINT));
	}
	shell->exit_shell = 42;
	if (shell->final_arguments[1] && !ft_atoicheck(shell->final_arguments[1]))
	{
		error_string = ft_strjoin("sushi: exit: ", shell->final_arguments[1]);
		error_string = ft_strjoinfree(error_string, ft_strdup(
					": numeric argument required"));
		return (error_handler(255, error_string, RESET_PRINT));
	}
	else if (shell->final_arguments[1])
		g_exit_status = ft_atoi(shell->final_arguments[1]);
	else
		g_exit_status = 0;
	return (error_handler(g_exit_status, NULL, RESET_PRINT));
}
