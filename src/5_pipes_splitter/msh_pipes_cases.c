/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:36:04 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:12:01 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_splitter.h"

int	handle_parenthesis(t_splitter *v)
{
	int		count_open;
	int		count_close;
	int		initial_cursor;

	count_open = 1;
	count_close = 0;
	initial_cursor = v->cursor;
	v->cursor = v->old_cursor;
	jointo_buffer(v, 0);
	v->cursor++;
	while (v->input[v->cursor])
	{
		ft_printd(0, "handling parentesis, v->cursor {%d}\n", v->cursor);
		jointo_buffer(v, 0);
		if (v->input[v->cursor] == ')')
			count_close++;
		else if ((int)v->cursor != initial_cursor && v->input[v->cursor] == '(')
			count_open++;
		if (count_open == count_close)
			break ;
		v->cursor++;
	}
	if (count_open != count_close)
		ft_printd(0, "ERROR IN HANDLE PARENTHESIS\n");
	return (EXIT_SUCCESS);
}

int	_case_pipe(t_splitter *v)
{
	if (is_pipe(v->input[v->old_cursor]))
		add_buffer(v, 1);
	return (EXIT_SUCCESS);
}

int	_case_pslit_parenthesis(t_splitter *v)
{
	if (is_parenthesis(v->input[v->old_cursor]))
	{
		if (handle_parenthesis(v))
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}
