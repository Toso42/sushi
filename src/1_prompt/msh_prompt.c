/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:21:07 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 11:51:46 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	is_a_memorable_command(char *input)
{
	char	*input_copy;
	int		yes_it_is;

	yes_it_is = 0;
	input_copy = ft_strtrim(input, " ");
	if (ft_strlen(input_copy))
		yes_it_is++;
	if (input_copy)
		free(input_copy);
	return (yes_it_is);
}

static int	_conditional_checks(t_shell *shell)
{
	if (g_exit_status)
	{
		shell->old_exit_status = g_exit_status;
		g_exit_status = 0;
	}
	if (!shell->input)
	{
		write(1, "exit\n", 5);
		exit(free_and_exit(shell));
	}
	if (shell->input && shell->input[0] == 0)
	{
		ft_printd(0, "ENTER_KEY?\n");
		shell->passing_through_process = 1;
		return (error_handler(shell->old_exit_status, NULL, DO_NOT_RESET));
	}
	if (is_a_memorable_command(shell->input))
		add_history(shell->input);
	if (_line_completion(shell))
	{
		ft_printd(0, "exit line_completion %d\n", g_exit_status);
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	msh_prompt(t_shell *shell)
{
	char	*prompt;

	sigint_control(MAIN_PROMPT);
	if (set_termios(TERMIOS_C_IGN))
	{
		free_and_exit(shell);
		return (1);
	}
	ft_printd(0, "assembling new prompt\n");
	prompt = assemble_prompt(NULL, 1);
	shell->input = readline(prompt);
	free(prompt);
	if (_conditional_checks(shell))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
