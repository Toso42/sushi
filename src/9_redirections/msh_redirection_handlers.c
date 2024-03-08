/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection_handlers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:12:34 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:25:34 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

int	_out_case(t_shell *shell, int argument_cursor)
{
	if (resolve_path(shell->final_arguments[argument_cursor + 1], READ_OK))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	shell->redirection_in = open(shell->final_arguments[argument_cursor + 1],
			O_RDONLY);
	dup2(shell->redirection_in, STDIN_FILENO);
	return (0);
}

void	_in_case(t_shell *shell, int argument_cursor)
{
	shell->redirection_out = open(shell->final_arguments[argument_cursor + 1],
			O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(shell->redirection_out, STDOUT_FILENO);
}

void	_append_case(t_shell *shell, int argument_cursor)
{
	shell->redirection_out = open(shell->final_arguments[argument_cursor + 1],
			O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(shell->redirection_out, STDOUT_FILENO);
}

int	handle_redirection(t_shell *shell, int a_cursor)
{
	char	*heredoc_complete;

	heredoc_complete = NULL;
	if (is_valid_redirection(shell->final_arguments[a_cursor]))
	{
		if (is_invalid_redirection_arg(shell->final_arguments[a_cursor + 1]))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
		if (!ft_strcmp_precision(shell->final_arguments[a_cursor], "<"))
			return (_out_case(shell, a_cursor));
		else if (!ft_strcmp_precision(shell->final_arguments[a_cursor], ">"))
			_in_case(shell, a_cursor);
		else if (!ft_strcmp_precision(shell->final_arguments[a_cursor], ">>"))
			_append_case(shell, a_cursor);
		else if (!ft_strcmp_precision(shell->final_arguments[a_cursor], "<<")
			&& _here_doc(shell, a_cursor, &heredoc_complete))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	msh_redirection_handler(t_shell *shell)
{
	int	argument_cursor;

	if (shell->passing_through_process
		|| !shell->final_arguments)
		return (EXIT_SUCCESS);
	argument_cursor = -1;
	while (shell->final_arguments[++argument_cursor])
	{
		if (is_valid_redirection(shell->final_arguments[argument_cursor])
			&& handle_redirection(shell, argument_cursor))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
		if (is_valid_redirection(shell->final_arguments[argument_cursor]))
		{
			shell->final_arguments = ft_sardel(shell->final_arguments,
					argument_cursor);
			shell->final_arguments = ft_sardel(shell->final_arguments,
					argument_cursor);
			argument_cursor = -1;
		}
	}
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
