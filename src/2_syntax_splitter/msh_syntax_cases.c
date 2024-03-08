/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:21:32 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:11:44 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_splitter.h"

int	_case_parenthesis(t_splitter *v)
{
	if (is_parenthesis(v->input[v->old_cursor]))
	{
		ft_printd(0, "is parenthesis\n");
		add_buffer(v, 1);
		jointo_buffer(v, 0);
		add_buffer(v, 1);
		v->cursor += 1;
	}
	return (EXIT_SUCCESS);
}

int	_case_l_redirection(t_splitter *v)
{
	if (is_redirection(v->input[v->old_cursor]))
	{
		if (v->bufferline)
			add_buffer(v, 1);
		if (redirection_lsplit_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_l_redirection"), DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_case_operator(t_splitter *v)
{
	if (is_operator(v->input[v->old_cursor]))
	{
		if (v->bufferline)
			add_buffer(v, 1);
		if (operator_lsplit_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_l_operator"), DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

static void	_copy_through_it(t_splitter *v)
{
	size_t	utility_cursor;

	utility_cursor = v->old_cursor;
	ft_printd(0, "_case_quote: dquote found, utility_c {%d}\n", utility_cursor);
	move_cursor_next_occurrence(&utility_cursor,
		v->input, v->input[v->old_cursor]);
	while (v->cursor <= utility_cursor)
	{
		jointo_buffer(v, 0);
		v->cursor += 1;
	}	
}

int	_case_quote(t_splitter *v)
{
	ft_printd(0, "entering _case_quote, |%d| {%c}\n",
		v->cursor, v->input[v->cursor]);
	if (is_dquote(v->input[v->old_cursor]))
		_copy_through_it(v);
	else if (is_squote(v->input[v->old_cursor]))
		_copy_through_it(v);
	ft_printd(0, "!!! exiting case quotes, bufferline: {%s}\n",
		v->bufferline);
	return (EXIT_SUCCESS);
}
