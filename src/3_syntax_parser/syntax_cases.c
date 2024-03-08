/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:08:33 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 18:40:01 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"

int	_case_parsing_operator(t_shell *shell, int cursor)
{
	if (is_valid_operator(shell->logical_split[cursor]))
	{
		ft_printd(0, "case_operator\n");
		if (_handle_operator(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_case_parsing_parenthesis(t_shell *shell, int cursor)
{
	if (is_parenthesis(shell->logical_split[cursor][0]))
	{
		ft_printd(0, "case_parenthesis\n");
		if (shell->logical_split[cursor][0] == '('
			&& _handle_open_parenthesis(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
		else if (shell->logical_split[cursor][0] == ')'
			&& _handle_close_parenthesis(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_case_parsing_redirection(t_shell *shell, int cursor)
{
	if (is_valid_redirection(shell->logical_split[cursor]))
	{
		ft_printd(0, "{%s} is_redirection", shell->logical_split[cursor]);
		if (_handle_redirection(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_case_parsing_command(t_shell *shell, int cursor)
{
	if (is_command(shell->logical_split[cursor]))
	{
		if (_handle_command(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}
