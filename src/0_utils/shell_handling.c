/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:19:52 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 15:34:07 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

/**
 * @brief init_shell inizializza le variabili dalla
 * struttura t_shell
 * 
 * @param shell structur
 */
int	free_and_exit(t_shell *shell)
{
	ft_sarfree(shell->envp, ft_sarsize(shell->envp));
	if (shell->pipes_split)
		ft_sarfree(shell->pipes_split, ft_sarsize(shell->pipes_split));
	if (shell->final_arguments)
		ft_sarfree(shell->final_arguments, ft_sarsize(shell->final_arguments));
	if (shell->logical_split)
	{
		ft_sarfree(shell->logical_split, ft_sarsize(shell->logical_split));
		shell->logical_split = NULL;
	}
	ft_free(shell->input);
	if (shell->process_description)
	{
		free(shell->process_description);
		shell->process_description = NULL;
	}
	if (shell->waiting_char)
	{
		free(shell->waiting_char);
		shell->waiting_char = NULL;
	}
	if (shell->is_terminal_process)
		rl_clear_history();
	set_termios(TERMIOS_C_DFL);
	return (g_exit_status);
}

void	shell_partial_reset(t_shell *shell)
{
	shell->pipes_counter = 0;
	shell->is_terminal_process = 0;
	shell->exit_shell = 0;
	shell->ctrld = 0;
	if (shell->final_arguments)
	{
		ft_sarfree(shell->final_arguments, ft_sarsize(shell->final_arguments));
		shell->final_arguments = NULL;
	}
	if (shell->waiting_char)
	{
		free(shell->waiting_char);
		shell->waiting_char = ft_strdup("");
	}
	if (shell->logical_split)
	{
		ft_sarfree(shell->logical_split, ft_sarsize(shell->logical_split));
		shell->logical_split = NULL;
	}
	if (shell->pipes_split)
	{
		ft_sarfree(shell->pipes_split, ft_sarsize(shell->pipes_split));
		shell->pipes_split = NULL;
	}
	shell->passing_through_process = 0;
}

static void	_reset_arrays(t_shell *shell)
{
	if (shell->pipes_split)
	{
		ft_sarfree(shell->pipes_split, ft_sarsize(shell->pipes_split));
		shell->pipes_split = NULL;
	}
	if (shell->final_arguments)
	{
		ft_sarfree(shell->final_arguments, ft_sarsize(shell->final_arguments));
		shell->final_arguments = NULL;
	}
	if (shell->logical_split)
	{
		ft_sarfree(shell->logical_split, ft_sarsize(shell->logical_split));
		shell->logical_split = NULL;
	}
	if (shell->waiting_char)
	{
		free(shell->waiting_char);
		shell->waiting_char = ft_strdup("");
	}
}

void	shell_reset(t_shell *shell)
{
	ft_printd(0, "resetting shell: {%s}\n", shell->process_description);
	_reset_redirections(shell);
	shell->pipes_counter = 0;
	shell->is_terminal_process = 0;
	shell->exit_shell = 0;
	shell->ctrld = 0;
	_reset_arrays(shell);
	ft_free(shell->input);
	error_handler(0, NULL, RESET_ERRORHANDLER);
	shell->passing_through_process = 0;
}

void	init_shell(t_shell *shell)
{
	shell->pipes_counter = 0;
	shell->logical_counter = 0;
	shell->pipes_split = NULL;
	shell->logical_split = NULL;
	shell->final_arguments = NULL;
	shell->is_terminal_process = 0;
	shell->old_exit_status = 0;
	shell->old_stdout = dup(STDOUT_FILENO);
	shell->old_stdin = dup(STDIN_FILENO);
	shell->process_level = 0;
	shell->process_description = ft_strdup("MAIN SHELL");
	g_exit_status = 0;
	shell->passing_through_process = 0;
	shell->waiting_char = ft_strdup("");
	shell->exit_shell = 0;
	shell->ctrld = 0;
	shell->envp = NULL;
}
