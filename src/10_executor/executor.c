/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:52:16 by kzak              #+#    #+#             */
/*   Updated: 2023/01/05 16:18:18 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_execute(t_shell *shell)
{
	char	*error_string;

	if (is_a_builtin(shell))
		return (error_handler(execute_builtins(shell), NULL, DO_NOT_RESET));
	else if (is_absolute_path(shell))
		return (error_handler(execute_absolute_path(shell), \
				NULL, DO_NOT_RESET));
	else if (is_a_program_name(shell, FOR_EXECUTOR) != NULL)
		return (error_handler(execute_program_name(shell), NULL, DO_NOT_RESET));
	else
	{
		error_string = ft_strjoinfree(ft_strdup("sushi: "),
				ft_strdup(shell->final_arguments[0]));
		error_string = ft_strjoinfree(error_string,
				ft_strdup(": command not found"));
		return (error_handler(127, error_string, DO_NOT_RESET));
	}
	return (g_exit_status);
}

int	msh_executor(t_shell *shell)
{
	if (shell->passing_through_process)
		return (EXIT_SUCCESS);
	if (shell->final_arguments)
		return (error_handler(_execute(shell), NULL, DO_NOT_RESET));
	if (shell->is_terminal_process)
	{
		shell->exit_shell = 42;
		exit(error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (error_handler(EXIT_SUCCESS, NULL, DO_NOT_RESET));
}
