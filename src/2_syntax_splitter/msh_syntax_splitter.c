/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_splitter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:21:40 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:19:58 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_splitter.h"

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

static int	is_above_args_c(t_splitter *v)
{
	if (is_eof(v->input[v->old_cursor])
		|| is_parenthesis(v->input[v->old_cursor])
		|| is_valid_operator(&v->input[v->old_cursor])
		|| is_dquote(v->input[v->old_cursor])
		|| is_squote(v->input[v->old_cursor])
		|| is_pipe(v->input[v->old_cursor])
		|| is_and(v->input[v->old_cursor])
		|| is_redirection(v->input[v->old_cursor]))
	{
		ft_printd(0, "is above arg\n");
		return (1);
	}
	return (0);
}

static int	_splitter_loop(t_splitter *v)
{
	ft_printd(0, "{%c} {%d}\n", v->input[v->cursor], v->cursor);
	v->old_cursor = v->cursor;
	if (_case_eof(v)
		|| _case_parenthesis(v)
		|| _case_quote(v)
		|| _case_operator(v)
		|| _case_l_redirection(v))
		return (EXIT_FAILURE);
	if (!is_above_args_c(v))
	{
		ft_printd(0, "splitter is NOT above arg, v->cursor {%d}, joining...\n",
			v->cursor);
		if (jointo_buffer(v, 0))
			return (EXIT_FAILURE);
		v->cursor += 1;
	}
	ft_printd(0, "splitter loop exiting, v->cursor {%d}\n", v->cursor);
	return (EXIT_SUCCESS);
}

int	msh_syntax_splitter(t_shell *shell)
{
	t_splitter	split_vars;
	t_splitter	*v;

	shell->pipes_counter = 0;
	v = NULL;
	v = _init_splitter(v, &split_vars, shell);
	if (!v->input)
		return (EXIT_SUCCESS);
	while (v->input[v->cursor] == ' ')
		v->cursor++;
	while (v->cursor <= (ft_strlen(v->input) + 1))
	{
		ft_printd(0, "{%c} {%d}\n", v->input[v->cursor], v->cursor);
		if (_splitter_loop(v))
			break ;
	}
	if (remove_space_args(v))
		return (error_handler(g_exit_status,
				ft_strdup("sushi: logical split space removal failed"),
				DO_NOT_RESET));
	shell->logical_split = v->result;
	ft_free(v->bufferline);
	if (!shell->logical_split)
		return (error_handler(shell->old_exit_status, NULL, DO_NOT_RESET));
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
