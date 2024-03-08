/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tdi-leo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:27:35 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/02 17:59:53 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

static int	_child(t_shell *shell, char *toprint, int *pipe_fd)
{
	if (shell->process_description)
		free(shell->process_description);
	shell->process_description = ft_strdup("pipe cmd process");
	shell->process_level += 1;
	shell->is_terminal_process = 1;
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if ((toprint) && strlen(toprint) > 0)
		ft_printf("%s\n", toprint);
	free(toprint);
	toprint = NULL;
	free(shell->process_description);
	shell->process_description = ft_strdup("child process printante\n");
	free_and_exit(shell);
	exit(EXIT_SUCCESS);
}

int	_spawn_and_print_heredoc(t_shell *shell, char *toprint)
{
	int	pipe_fd[2];
	int	pid;
	int	pexit_status;

	sigint_control(C_IGNORE);
	pexit_status = 0;
	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		g_exit_status = 1;
	if (!pid)
		exit(_child(shell, toprint, pipe_fd));
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pid, &pexit_status, 0);
	sigint_control(MAIN_PROMPT);
	ft_free(toprint);
	pexit_status = WEXITSTATUS(pexit_status);
	if (pexit_status == EXIT_SHELL)
		exit(EXIT_SHELL);
	free(shell->process_description);
	shell->process_description = ft_strdup("main process ricevente\n");
	return (EXIT_SUCCESS);
}

static int	_heredoc_prompt(t_heredoc *hd, t_shell *shell, int argument_cursor)
{
	ft_free(hd->heredoc_swap);
	hd->heredoc_line = ft_strdup("");
	if (_open_new_prompt(shell, &hd->heredoc_line, HEREDOC))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	free(shell->process_description);
	shell->process_description = ft_strdup("main process HERE_DOC\n");
	if (shell->ctrld == 1)
	{
		ft_free(hd->heredoc_line);
		return (1);
	}
	if (!ft_strcmp_precision(hd->heredoc_line,
			shell->final_arguments[argument_cursor + 1]))
	{
		ft_free(hd->heredoc_line);
		return (1);
	}
	hd->heredoc_swap = ft_strdup(hd->heredoc_line);
	if (++hd->line_counter > 0)
		hd->heredoc_line = ft_strjoinfree(ft_strdup("\n"), hd->heredoc_line);
	else
		hd->heredoc_line = ft_strjoinfree(ft_strdup(""), hd->heredoc_line);
	hd->heredoc_complete[0] = ft_strjoinfree(hd->heredoc_complete[0],
			hd->heredoc_line);
	return (0);
}

static void	_init_hd(t_heredoc *hd, char **heredoc_complete, t_shell *shell,
	int argument_cursor)
{
	hd->heredoc_line = NULL;
	hd->heredoc_swap = ft_strdup("");
	hd->heredoc_complete = heredoc_complete;
	hd->heredoc_complete[0] = ft_strdup("");
	hd->line_counter = -1;
	ft_free(shell->waiting_char);
	shell->waiting_char = ft_strdup(
			shell->final_arguments[argument_cursor + 1]);
	hd->stdout_swap = dup(STDOUT_FILENO);
	hd->stdin_swap = dup(STDIN_FILENO);
}

int	_here_doc(t_shell *shell, int argument_cursor, char**heredoc_complete)
{
	t_heredoc	hd;

	_init_hd(&hd, heredoc_complete, shell, argument_cursor);
	ft_printd(0, ">>>> HERE DOC!\n");
	dup2(shell->old_stdout, STDOUT_FILENO);
	dup2(shell->old_stdin, STDIN_FILENO);
	while (ft_strcmp_precision(hd.heredoc_swap,
			shell->final_arguments[argument_cursor + 1]) \
		|| shell->final_arguments[argument_cursor + 1][0] == 0)
	{
		if (_heredoc_prompt(&hd, shell, argument_cursor))
			break ;
	}
	ft_printd(0, "exiting heredoc: {%s}\n", heredoc_complete[0]);
	dup2(hd.stdout_swap, STDOUT_FILENO);
	dup2(hd.stdin_swap, STDIN_FILENO);
	_spawn_and_print_heredoc(shell, heredoc_complete[0]);
	return (EXIT_SUCCESS);
}
