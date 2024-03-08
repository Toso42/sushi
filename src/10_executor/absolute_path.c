/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:18:08 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:28:11 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	_child_absolute(t_shell *shell)
{
	char	*error_string;

	sigint_control(C_RESET);
	sigquit_control(QUIT_RESET);
	set_termios(TERMIOS_C_DFL);
	shell->process_level += 1;
	ft_free(shell->process_description);
	shell->process_description = ft_strdup("execve process");
	shell->is_terminal_process = 1;
	if (execve(shell->final_arguments[0], shell->final_arguments, \
		shell->envp))
	{
		error_string = ft_strjoinfree(ft_strdup("sushi: "), \
			ft_strdup(shell->final_arguments[0]));
		error_string = ft_strjoinfree(error_string, \
			ft_strdup(": Is a directory"));
		exit(error_handler(126, error_string, DO_NOT_RESET));
	}
	exit(error_handler(0, NULL, DO_NOT_RESET));
}

int	execute_absolute_path(t_shell *shell)
{
	int	fork_exve;

	if (g_exit_status == 127)
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	sigint_control(C_IGNORE);
	fork_exve = fork();
	if (!fork_exve)
		_child_absolute(shell);
	waitpid(fork_exve, &g_exit_status, 0);
	if (WIFSIGNALED(g_exit_status))
		return (error_handler(signal_detected(shell), NULL, DO_NOT_RESET));
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	if (g_exit_status)
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}

int	_check_with_pwd(t_shell *shell)
{
	char	*swap_str;

	swap_str = ft_strjoinfree(msh_get_env_value(shell->envp, "PWD"),
			ft_strdup("/"));
	swap_str = ft_strjoinfree(swap_str, ft_strdup(shell->final_arguments[0]));
	if (!access(swap_str, F_OK))
	{
		free(swap_str);
		return (1);
	}
	free(swap_str);
	return (error_directory(shell, 0));
}

int	is_absolute_path(t_shell *shell)
{
	if (ft_strnstr(shell->final_arguments[0], "/", \
		ft_strlen(shell->final_arguments[0])))
	{
		if (ft_strnstr(shell->final_arguments[0], "/", 1))
		{
			if (!access(shell->final_arguments[0], F_OK))
				return (1);
			else
				return (error_handler(error_directory(shell, 0), NULL, \
					DO_NOT_RESET));
		}
		else
		{
			return (_check_with_pwd(shell));
		}
	}
	return (0);
}
