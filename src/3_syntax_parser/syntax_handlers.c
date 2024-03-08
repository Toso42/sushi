/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:12:11 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 23:17:11 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"

static int	_par_eval(t_shell *shell, t_splitter *v, int *open, int *close)
{
	if (!shell->logical_split[v->cursor] && open[0] > close[0])
		return (error_handler(258, assemble_error(1, shell, v->cursor),
				DO_NOT_RESET));
	if (shell->logical_split[v->cursor][0] == ')')
	{
		if (v->cursor == v->old_cursor + 1)
			return (error_handler(258, assemble_error(2, shell, v->cursor),
					DO_NOT_RESET));
		close[0]++;
	}
	if (shell->logical_split[v->cursor][0] == '(')
		open[0]++;
	if (open[0] == close[0])
		return (0);
	if (is_valid_operator(shell->logical_split[v->cursor])
		&& v->cursor == v->old_cursor + 1)
		return (error_handler(258, assemble_error(2, shell, v->cursor),
				DO_NOT_RESET));
	return (0);
}

/**
 * @brief syntax checks for open parentheses (and so on for the rest).
 * 
 * @param shell 
 * @param v->cursor 
 * @return int 
 */
int	_handle_open_parenthesis(t_shell *shell, int cursor)
{
	int			open;
	int			close;
	t_splitter	v;

	open = 1;
	close = 0;
	v.old_cursor = cursor;
	v.cursor = cursor;
	ft_printd(0, "_handle_open_parenthesis\n");
	while (shell->logical_split[++v.cursor])
	{
		if (_par_eval(shell, &v, &open, &close))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	if (open > close)
		return (error_handler(258, assemble_error(1, shell, cursor),
				DO_NOT_RESET));
	return (EXIT_SUCCESS);
}

int	_handle_close_parenthesis(t_shell *shell, int cursor)
{
	ft_printd(0, "_handle_close_parenthesis\n");
	cursor++;
	if (!shell->logical_split[cursor])
		return (EXIT_SUCCESS);
	if (shell->logical_split[cursor][0] == '('
		|| is_command(shell->logical_split[cursor]))
	{
		return (error_handler(2, assemble_error(2, shell, cursor),
				DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_handle_operator(t_shell *shell, int cursor)
{
	ft_printd(0, "_handle_case_operator\n");
	if (!shell->logical_split[++cursor])
		return (error_handler(2, assemble_error(1, shell, cursor),
				DO_NOT_RESET));
	if (shell->logical_split[cursor][0] == ')')
		return (error_handler(2, assemble_error(2, shell, cursor),
				DO_NOT_RESET));
	if (is_valid_operator(shell->logical_split[cursor]))
		return (error_handler(2, assemble_error(2, shell, cursor),
				DO_NOT_RESET));
	return (EXIT_SUCCESS);
}
