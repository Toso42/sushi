/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:22:49 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/09 10:44:01 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/* These functions evaluate if input[cursor] is a specific case. If so, they 
conditionally execute case_specific handling functions.*/
int	_case_redirection(t_splitter *v)
{
	if (is_redirection(v->input[v->old_cursor]))
	{
		if (v->bufferline)
			add_buffer(v, 1);
		if (redirection_section_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_dquote"), DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}

int	_case_dquote(t_splitter *v)
{
	ft_printd(0, "*** entering DQUOTE [%d]\n", v->old_cursor);
	if (is_dquote(v->input[v->old_cursor]))
	{
		if (dquote_section_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_dquote"), DO_NOT_RESET));
	}
	ft_printd(0, "*** [%d]\n", v->old_cursor);
	return (EXIT_SUCCESS);
}

int	_case_squote(t_splitter *v)
{
	ft_printd(0, "*** entering SQUOTE [%d]\n", v->old_cursor);
	if (is_squote(v->input[v->old_cursor]))
	{
		if (squote_section_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_squote"), DO_NOT_RESET));
	}
	ft_printd(0, "*** [%d]\n", v->old_cursor);
	return (EXIT_SUCCESS);
}

int	_case_regular_separator(t_splitter *v)
{
	if (is_regular_separator(v->input[v->old_cursor]))
	{
		ft_printd(0, "*** entering SEP [%d]\n", v->old_cursor);
		if (spaces_handler(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_regular_separator"), DO_NOT_RESET));
	}
	ft_printd(0, "*** [%d]\n", v->old_cursor);
	return (EXIT_SUCCESS);
}

/**
 * @brief Specific Case switcher for $ operators found on v.input. $$ operator
 * is intercepted and handled here and in _literal_buffer loop, for the moment.
 * 
 * @param v 
 * @return int 
 */
int	_case_var(t_splitter *v)
{
	if (is_var(v->input[v->old_cursor]))
	{
		ft_printd(0, "entering VAR, cursor{%d}\n", v->old_cursor);
		if (v->input[v->old_cursor + 1] == '?')
		{
			if (handle_exit_status(v))
			{
				ft_printd(0, "Exit_status expansion\n");
				return (error_handler(g_exit_status,
						ft_strdup("!!! _case_VAR"), DO_NOT_RESET));
			}
		}
		else if (is_var(v->input[v->old_cursor + 1]))
		{
			if (!v->bufferline)
				v->bufferline = ft_strdup("");
			v->bufferline = ft_strjoinfree(v->bufferline,
					ft_itoa((int)getpid()));
			v->cursor += 2;
		}
		else if (handle_var(v))
			return (error_handler(g_exit_status,
					ft_strdup("!!! _case_VAR"), DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}
