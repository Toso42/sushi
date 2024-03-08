/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:36:11 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:19:34 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_splitter.h"

static t_splitter	*_init_splitter(t_splitter *v, t_splitter *split_vars,
		t_shell *shell)
{
	v = split_vars;
	v->cursor = 0;
	v->old_cursor = 0;
	v->nl_cursor = 0;
	v->envp = shell->envp;
	v->input = shell->input;
	v->bufferline = NULL;
	v->result = NULL;
	v->handling_dquote = 0;
	v->old_exit_status = shell->old_exit_status;
	return (v);
}

static int	_splitter_loop(t_splitter *v)
{
	ft_printd(0, "{%c} {%d}\n", v->input[v->cursor], v->cursor);
	v->old_cursor = v->cursor;
	if (_case_eof(v)
		|| _case_pipe(v)
		|| _case_quote(v)
		|| _case_pslit_parenthesis(v))
		return (EXIT_FAILURE);
	ft_printd(0, "old cursor char {%c} [%d]\n",
		v->input[v->old_cursor], v->old_cursor);
	if (!is_pipe(v->input[v->old_cursor])
		&& !is_parenthesis(v->input[v->old_cursor])
		&& !is_dquote(v->input[v->old_cursor])
		&& !is_squote(v->input[v->old_cursor])
		&& jointo_buffer(v, 0))
		return (EXIT_FAILURE);
	if (!is_dquote(v->input[v->old_cursor])
		&& !is_squote(v->input[v->old_cursor]))
		v->cursor += 1;
	ft_printd(0, "splitter loop exiting, v->cursor {%d}\n", v->cursor);
	return (EXIT_SUCCESS);
}

int	msh_pipes_splitter(t_shell *shell)
{
	t_splitter	split_vars;
	t_splitter	*v;

	if (shell->passing_through_process)
		return (EXIT_SUCCESS);
	v = NULL;
	v = _init_splitter(v, &split_vars, shell);
	ft_printd(0, "ENTERING SPLITTER\n");
	while (v->input[v->cursor] == ' ')
		v->cursor++;
	while (v->cursor <= (ft_strlen(v->input) + 1))
	{
		ft_printd(0, "{%c} {%d}\n", v->input[v->cursor], v->cursor);
		if (_splitter_loop(v))
		{
			shell->pipes_split = v->result;
			if (g_exit_status)
				return (error_handler(g_exit_status,
						ft_strdup("!!! INSIDE pipes_Splitter"), DO_NOT_RESET));
			break ;
		}
	}
	shell->pipes_split = v->result;
	ft_free(v->bufferline);
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
