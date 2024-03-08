/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes_forker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:33:07 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 21:44:35 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_forker.h"

int	_conditional_wait_forked_p(t_shell *shell, int pid,
	int last_process_flag)
{
	int	pexit_status;

	pexit_status = 0;
	if (last_process_flag)
	{
		waitpid(pid, &pexit_status, 0);
		if (WIFEXITED(pexit_status))
			pexit_status = WEXITSTATUS(pexit_status);
		if (pexit_status == EXIT_SHELL)
		{
			shell->exit_shell = 42;
			exit(g_exit_status);
		}
		return (error_handler(pexit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_create_pipe_fork_process(t_shell *shell, int last_process_flag, int *pids)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	pids[shell->pipes_counter] = fork();
	if (pids[shell->pipes_counter] < 0)
		g_exit_status = 1;
	if (!pids[shell->pipes_counter])
	{
		ft_free(shell->input);
		shell->input = ft_strdup(shell->pipes_split[shell->pipes_counter]);
		shell_partial_reset(shell);
		free(pids);
		pids = NULL;
		exit(_prepare_struct_redirect_fd(shell, last_process_flag, pipe_fd));
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}

int	search_parentheses_in_input(char *input)
{
	if (ft_strchr(input, '('))
		return (1);
	return (0);
}

static int	_one_command(t_shell *shell, int pip_counter)
{
	if ((search_parentheses_in_input(shell->input) && pip_counter <= 1))
	{
		ft_printd(0, "prepare and execute compound command\n");
		return (error_handler(subshell_fork(shell,
					compound_command_preparations(shell)), NULL,
				RESET_PRINT));
	}
	ft_printd(0, "__Ex.ng pipforker {%s}: no par or only one argument.\n",
		shell->process_description);
	return (EXIT_SUCCESS);
}

/**
 * @brief This function assesses if a pipeline consists of more than 1 command,
 * if so, the pipes_forker loops through the command array creating a pipe() 
 * each, forking each command and redirecting it accordingly (so that each 
 * command writes into the next one's stdin.). Last command is made to write 
 * back into the original stdout.
 * 
 * @param shell 
 * @return int 
 */
int	msh_pipes_forker(t_shell *shell)
{
	int	pip_counter;
	int	pexit_status;
	int	last_process_flag;
	int	*pids;

	pip_counter = ft_sarsize(shell->pipes_split);
	last_process_flag = 0;
	if (pip_counter <= 1 || shell->passing_through_process)
		return (_one_command(shell, pip_counter));
	pids = (int *) malloc (sizeof(int) * pip_counter);
	while ((int)shell->pipes_counter < (pip_counter))
	{
		if ((int)shell->pipes_counter == (pip_counter - 1))
			last_process_flag = 1;
		pexit_status = _create_pipe_fork_process(shell, last_process_flag,
				pids);
		shell->pipes_counter += 1;
		if ((int)shell->pipes_counter == (pip_counter))
			g_exit_status = pexit_status;
	}
	_finalize(shell, pip_counter, pids, last_process_flag);
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
