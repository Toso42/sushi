/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:32:43 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:29:26 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*_check_with_path(t_shell *shell, int flag, int cursor, \
								char **split_path)
{
	char	*path_com;

	path_com = NULL;
	while (split_path[++cursor])
	{
		split_path[cursor] = ft_strjoinfree(split_path[cursor], ft_strdup("/"));
		path_com = ft_strjoin(split_path[cursor], shell->final_arguments[0]);
		if (!access(path_com, F_OK))
		{
			if (flag == FOR_EXECUTOR)
			{
				ft_sarfree(split_path, ft_sarsize(split_path));
				free(path_com);
				return ("ok");
			}
			if (flag == FOR_EXECVE)
			{
				ft_sarfree(split_path, ft_sarsize(split_path));
				return (path_com);
			}
		}
		free(path_com);
	}
	ft_sarfree(split_path, ft_sarsize(split_path));
	return (NULL);
}

char	*is_a_program_name(t_shell *shell, int flag)
{
	char	**split_path;
	int		cursor;

	if (shell->final_arguments[0] && shell->final_arguments[0][0] == '\0')
		return (NULL);
	cursor = 0;
	while (shell->envp[cursor] && !ft_strnstr(shell->envp[cursor], "PATH", 4))
		cursor++;
	if (!shell->envp[cursor])
		return (shell->final_arguments[0]);
	split_path = ft_split(shell->envp[cursor] + 5, ':');
	cursor = -1;
	return (_check_with_path(shell, flag, cursor, split_path));
}

static void	_child_execute(t_shell *shell)
{
	sigint_control(C_RESET);
	sigquit_control(QUIT_RESET);
	set_termios(TERMIOS_C_DFL);
	shell->process_level += 1;
	ft_free(shell->process_description);
	shell->process_description = ft_strdup("execve process");
	shell->is_terminal_process = 1;
	execve(is_a_program_name(shell, FOR_EXECVE), \
			shell->final_arguments, shell->envp);
}

int	execute_program_name(t_shell *shell)
{
	int	fork_exve;

	if (!env_strncmp(shell, "PATH"))
		return (error_handler(error_directory(shell, 0), NULL, DO_NOT_RESET));
	fork_exve = fork();
	sigint_control(C_IGNORE);
	if (!fork_exve)
	{
		_child_execute(shell);
	}
	waitpid(fork_exve, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	if (WIFSIGNALED(g_exit_status))
		return (error_handler(signal_detected(shell), NULL, DO_NOT_RESET));
	if (g_exit_status)
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	return (0);
}
