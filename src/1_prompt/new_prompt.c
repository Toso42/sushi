/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:11:44 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 17:09:04 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	_wait_sub_prompt(t_shell *shell, int pid, int *pipe_fd)
{
	int	pexit_status;

	sigint_control(C_IGNORE);
	close(pipe_fd[1]);
	waitpid(pid, &pexit_status, 0);
	if (shell->waiting_char)
	{
		free(shell->waiting_char);
		shell->waiting_char = ft_strdup("");
	}
	if (WIFEXITED(pexit_status))
	{
		g_exit_status = WEXITSTATUS(pexit_status);
		ft_printd(0, "from main, child e_s = {%d}\n", g_exit_status);
		if (g_exit_status == 130)
			g_exit_status += 128;
		if (g_exit_status == 142)
		{
			shell->ctrld = 1;
			g_exit_status = 0;
		}
		if (g_exit_status)
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (0);
}

static int	_evaluate_readenline(char **promptline, int *pipe_fd,
	int string_size)
{
	char	*readenline;

	ft_printd(0, "size more than 0\n");
	readenline = (char *)malloc(sizeof(char) * string_size + 1);
	ft_printd(0, "Before pipe reading, string: \n%s\n", readenline);
	read(pipe_fd[0], readenline, (sizeof(char) * (string_size + 1)));
	ft_printd(0, "String readen: \n%s\n", readenline);
	promptline[0] = ft_strdup(readenline);
	ft_printd(0, "_o_n_p has readen: {%s}\n", readenline);
	free(readenline);
	ft_printd(0, "parent prompt returning with non null string_size\n");
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}

int	_open_new_prompt(t_shell *shell, char **promptline, int flag)
{
	int		pid;
	int		string_size;
	int		pipe_fd[2];

	ft_free(promptline[0]);
	promptline[0] = NULL;
	pipe(pipe_fd);
	sigint_control(C_RESET);
	pid = fork();
	free(shell->process_description);
	shell->process_description = ft_strdup("After new prompt");
	if (!pid)
		_sub_prompt(shell, pipe_fd, flag);
	if (_wait_sub_prompt(shell, pid, pipe_fd))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	ft_printd(0, "Parent has done waiting\n");
	read(pipe_fd[0], &string_size, sizeof(int));
	ft_printd(0, "Parent has readen string_size: %d\n", string_size);
	if ((string_size > 0)
		&& _evaluate_readenline(promptline, pipe_fd, string_size))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	ft_printd(0, "parent prompt returning with NULL string_size\n");
	if (!promptline[0])
		promptline[0] = ft_strdup("");
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
