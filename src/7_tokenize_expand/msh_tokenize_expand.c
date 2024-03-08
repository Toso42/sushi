/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tokenize_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:23:04 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/09 10:54:14 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/**
 * @brief an implicit struct initializer.
 * 
 * @param v 
 * @param split_vars 
 * @param shell 
 * @return t_splitter* 
 */
static t_splitter	*_init_splitter(t_splitter *v, t_splitter *split_vars,
	t_shell *shell)
{
	v = split_vars;
	v->cursor = 0;
	v->old_cursor = 0;
	v->nl_cursor = 0;
	v->envp = shell->envp;
	if (ft_sarsize(shell->pipes_split) > 1)
		v->input = shell->pipes_split[shell->pipes_counter];
	else
		v->input = shell->input;
	v->bufferline = NULL;
	v->result = NULL;
	v->handling_dquote = 0;
	v->old_exit_status = shell->old_exit_status;
	return (v);
}

/**
 * @brief A double check (necessary for 42Norm -25 line per function- rule) 
 * to make sure the unconditional append to buffer is not called upon specific
 * cases, which should be handled differently.
 * 
 * @param v 
 * @return int 
 */
static int	is_above_args(t_splitter *v)
{
	if (is_eof(v->input[v->old_cursor])
		|| is_regular_separator(v->input[v->old_cursor])
		|| is_var(v->input[v->old_cursor])
		|| is_squote(v->input[v->old_cursor])
		|| is_dquote(v->input[v->old_cursor])
		|| is_redirection(v->input[v->old_cursor]))
		return (1);
	return (0);
}

/**
 * @brief The expander loop looks whether shell.input[cursor] might be a 
 * specific case, and if so, it calls case_specific functions. If a 
 * specific_case is not found, the current char is unconditionally appended 
 * to the buffer string.
 * 
 * @param v 
 * @return int 
 */
static int	_expander_loop(t_splitter *v)
{
	ft_printd(0, "{%c} {%d}\n", v->input[v->cursor], v->cursor);
	v->old_cursor = v->cursor;
	if (_case_eof(v)
		|| _case_regular_separator(v)
		|| _case_var(v)
		|| _case_squote(v)
		|| _case_dquote(v)
		|| _case_redirection(v))
	{
		ft_printd(0, "_case exited failure\n");
		return (EXIT_FAILURE);
	}
	if (is_above_args(v) == 0)
	{
		ft_printd(0, "{%c} {%d} is NOT an above arg, joining and adding one\n",
			v->input[v->cursor], v->cursor);
		if (jointo_buffer(v, 0))
			return (EXIT_FAILURE);
		v->cursor += 1;
	}
	else
		ft_printd(0, "{%c} {%d} IS an above arg, it should have been handled\n",
			v->input[v->old_cursor], v->old_cursor);
	ft_printd(0, "EXITING LOOP, cursor: {%d}\n", v->cursor);
	return (EXIT_SUCCESS);
}

/**
 * @brief The Expander function reads Shell.input in search of arguments to 
 * pass to the executor. It reads the input string one char at a time, through 
 * the use of a size_t cursor. If input[cursor] is found to be a special
 * case delimiter, an handling function is launched to parse the argument and 
 * add it to the shell.buffer.
 * All other chars, except for separators, are added to the buffer string. 
 * If input[cursor] is found to be a terminator symbol or character,the 
 * shell.bufferline is finalized as an argument, and "appended" to the
 * shell.final_arguments strings array. The cycle goes on until an EndOfFile is
 * found.
 * To adhere to the 42 norm and it's function-lenght limitation, the cursor 
 * movement is completely handled by the case_handling functions (cursor 
 * handling is implicit within handlers, one level above _case_functions).
 * If the cursor points to a specific case, the cursor is moved externally after
 * a buffer join.
 * 
 * @param shell struct
 * @return int error_handler().
 */
int	msh_tokenize_expand(t_shell *shell)
{
	t_splitter	split_vars;
	t_splitter	*v;

	if (shell->passing_through_process)
		return (EXIT_SUCCESS);
	v = NULL;
	v = _init_splitter(v, &split_vars, shell);
	while (v->cursor <= (ft_strlen(v->input) + 1))
	{
		if (_expander_loop(v))
		{
			shell->final_arguments = v->result;
			if (g_exit_status)
			{
				ft_free(v->bufferline);
				return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
			}
			break ;
		}
	}
	shell->final_arguments = v->result;
	ft_free(v->bufferline);
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
