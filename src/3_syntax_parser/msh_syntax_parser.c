/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:07 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 10:50:34 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../2_syntax_splitter/s_splitter.h"

int	is_invalid_redirection_arg(char *token)
{
	if (!is_command(token))
	{
		return (1);
	}
	return (EXIT_SUCCESS);
}

char	*assemble_error(int flag, t_shell *shell, int cursor)
{
	char	*new_error;

	new_error = NULL;
	if (flag == 1)
	{
		new_error = ft_strjoinfree(
				ft_strdup("sushi: syntax error: near unexpected token `"),
				ft_strdup("EOF"));
		new_error = ft_strjoinfree(new_error, ft_strdup("\'"));
	}
	if (flag == 2)
	{
		new_error = ft_strjoinfree(
				ft_strdup("sushi: syntax error near unexpected token `"),
				ft_strdup(shell->logical_split[cursor]));
		new_error = ft_strjoinfree(new_error, ft_strdup("\'"));
	}
	if (flag == 3)
	{
		new_error = ft_strjoinfree(
				ft_strdup("sushi: syntax error near unexpected token `"),
				ft_char_to_str(shell->logical_split[cursor][0]));
		new_error = ft_strjoinfree(new_error, ft_strdup("\'"));
	}
	return (new_error);
}

/**
 * @brief The Syntax Parser parses the input for syntax errors. If an error
 * is met, an error is assembled and fed to the error_handler.
 * 
 * @param shell 
 * @return int 
 */
int	msh_syntax_parser(t_shell *shell)
{
	int	cursor;

	cursor = -1;
	if (!shell->logical_split)
	{
		shell->passing_through_process = 1;
		return (EXIT_SUCCESS);
	}
	ft_printd(0, "iniziando il logical parser\n");
	while (shell->logical_split[++cursor])
	{
		ft_printd(0, "parsing {%s}\n", shell->logical_split[cursor]);
		if (_case_parsing_parenthesis(shell, cursor)
			|| _case_parsing_operator(shell, cursor)
			|| _case_parsing_command(shell, cursor)
			|| _case_parsing_redirection(shell, cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	ft_printd(0, "_LOGIC PARSING SUCCESS\n");
	return (EXIT_SUCCESS);
}
