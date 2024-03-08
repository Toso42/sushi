/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:43:52 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:55:04 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(int errno, char *errmex, int flag_reset)
{
	static int	errmex_isprinted;

	if (errmex_isprinted == ERHANLER_CAN_PRINT)
	{
		if (errmex)
		{
			ft_printfd(STDERR_FILENO, "%s\n", errmex);
			errmex_isprinted = ERHANLER_CANNOT_PRINT;
		}
		g_exit_status = errno;
	}
	if (flag_reset == RESET_ERRORHANDLER)
	{
		g_exit_status = 0;
		errmex_isprinted = ERHANLER_CAN_PRINT;
	}
	else if (flag_reset == RESET_PRINT)
		errmex_isprinted = ERHANLER_CAN_PRINT;
	if (errmex)
	{
		free(errmex);
		errmex = NULL;
	}
	return (g_exit_status);
}

void	_reset_redirections(t_shell *shell)
{
	dup2(shell->old_stdout, STDOUT_FILENO);
	dup2(shell->old_stdin, STDIN_FILENO);
}

/**
 * @brief The main routine. Logical forker(1) and pipes forker(2) might
 * conditionally create a subroutine if (1) operators are found or (2)
 * pipelines are found. Only simple commands pass the two forkers and
 * complete the main_routine.
 * In case (1) and (2) the main process whill set a pass_through flag 
 * to skip remaining steps and start again from main_loop.
 * 
 * @param shell 
 * @param utility_flag 
 * @return int 
 */
static int	main_routine(t_shell *shell, int *utility_flag)
{
	if (msh_prompt(shell)
		|| msh_syntax_splitter(shell)
		|| msh_syntax_parser(shell)
		|| msh_logical_forker(shell)
		|| msh_pipes_splitter(shell)
		|| msh_pipes_forker(shell)
		|| msh_tokenize_expand(shell)
		|| msh_namefile_expansion(shell)
		|| msh_redirection_handler(shell)
		|| msh_executor(shell))
	{
		ft_printd(0, "\nSomething wrong in main process: %d %s\n\n",
			g_exit_status, shell->process_description);
		shell->old_exit_status = g_exit_status;
		if (shell->exit_shell == EXIT_SHELL)
			return (EXIT_SHELL);
		shell_reset(shell);
		utility_flag[0] = 1;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief main_loop is set_up to run the main_routine ad libitum. To make room
 * for debug prints, an utility flag is created to divert interrupted routines
 * and succesful ones.
 * 
 * @param shell 
 * @return int 
 */
int	main_loop(t_shell *shell)
{
	int	utility_flag;

	utility_flag = 0;
	g_exit_status = 0;
	shell->is_terminal_process = 0;
	dup2(shell->old_stdin, STDIN_FILENO);
	while (1)
	{
		if (main_routine(shell, &utility_flag) == EXIT_SHELL)
			return (EXIT_SUCCESS);
		if (utility_flag == 0)
		{
			shell->old_exit_status = g_exit_status;
			if (shell->exit_shell == EXIT_SHELL)
				return (EXIT_SUCCESS);
			shell_reset(shell);
		}
		utility_flag = 0;
	}
	return (g_exit_status);
}

/**
 * @brief Header print and shell struct preparations.
 * 
 * @param argc 
 * @param argv 
 * @param env 
 * @return int 
 */
int	main(int argc, char **argv, char **env)
{
	t_shell			shell;
	struct winsize	win;

	(void)argv;
	if (argc > 1)
		return (error_handler(1, ft_strdup("Only ./minishell"),
				DO_NOT_RESET));
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	if (win.ws_col >= 121)
		print_long_header();
	else if (win.ws_col >= 60)
		print_short_header();
	init_shell(&shell);
	copy_set_env(&shell, env);
	assemble_prompt(&shell, 0);
	sigquit_control(QUIT_IGNORE);
	assemble_prompt(&shell, 0);
	main_loop(&shell);
	return (free_and_exit(&shell));
}
