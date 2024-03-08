/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:03:28 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 21:40:41 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_forker.h"

int	_pipes_sub_routine(t_shell *shell)
{
	if (msh_syntax_splitter(shell)
		|| msh_syntax_parser(shell)
		|| msh_logical_forker(shell)
		|| msh_pipes_splitter(shell)
		|| msh_pipes_forker(shell)
		|| msh_tokenize_expand(shell)
		|| msh_namefile_expansion(shell)
		|| msh_redirection_handler(shell)
		|| msh_executor(shell))
	{
		free_and_exit(shell);
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	free_and_exit(shell);
	return (g_exit_status);
}

/**
 * @brief Creates a subshell struct, subshell.input = new_input. It
 * then forks the subshell, and exit it's sub_routine.
 * 
 * @param shell 
 * @param new_input 
 * @return int 
 */
int	subshell_fork(t_shell *shell, char *new_input)
{
	t_shell	subshell;
	int		pid;
	int		sub_exit;

	ft_printd(0, "printing on subshell stdout before struct creation\n");
	init_shell(&subshell);
	subshell.input = new_input;
	subshell.envp = ft_sarcopy(shell->envp);
	pid = fork();
	if (!pid)
	{
		ft_free(subshell.process_description);
		subshell.process_description = ft_strdup("subshell cmd process");
		subshell.process_level += 1;
		subshell.is_terminal_process = 1;
		ft_printd(0, "printing on subshell stdout\n");
		free_and_exit(shell);
		exit(_pipes_sub_routine(&subshell));
	}
	waitpid(pid, &sub_exit, 0);
	if (WIFEXITED(sub_exit))
		sub_exit = WEXITSTATUS(sub_exit);
	free_and_exit(&subshell);
	shell->passing_through_process = 1;
	return (sub_exit);
}

char	*expand_parenthesis(t_shell *shell)
{
	char	*new_input;

	new_input = NULL;
	ft_printd(0, "!!!par espansion. from: {%s} to {%s}\n",
		shell->input, new_input);
	new_input = (char *)malloc(sizeof(char) * (ft_strlen(shell->input) - 1));
	ft_strlcpy(new_input, &shell->input[1],
		(ft_strlen(shell->input) - 1));
	ft_printd(0, "!!!par espansion. from: {%s} to {%s}\n",
		shell->input, new_input);
	return (new_input);
}

/**
 * inside here shell struct get modified and redirected accordingly.
 * Inside here each pipe child is still the same. If cmd is enveloped
 * by a parenthesis, parenthesis is expanded and argument is passed
 * to a subshell.
*/
int	_prepare_struct_redirect_fd(t_shell *shell, int last_process_flag,
	int pipe_fd[2])
{
	ft_free(shell->process_description);
	shell->process_description = ft_strdup("pipe cmd process");
	shell->process_level += 1;
	shell->is_terminal_process = 1;
	if (last_process_flag)
		dup2(shell->old_stdout, STDOUT_FILENO);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (search_parentheses_in_input(shell->input))
	{
		ft_printd(0, "__forking parenthesis pipe: {%s}\n", shell->input);
		return (error_handler(subshell_fork(shell,
					compound_command_preparations(shell)), NULL, RESET_PRINT));
	}
	else
		return (_pipes_sub_routine(shell));
	free_and_exit(shell);
	return (EXIT_SUCCESS);
}
