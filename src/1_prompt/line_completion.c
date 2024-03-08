/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:11:42 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 17:07:35 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	_check_for_quotes(t_shell *shell, int x, size_t *quote_cursor)
{
	ft_printd(0, "searching incompelte dquotes\n");
	if (((shell->input[x] == '\"')
			&& move_cursor_next_occurrence(quote_cursor, shell->input, '\"'))
		|| ((shell->input[x] == '\'')
			&& move_cursor_next_occurrence(quote_cursor, shell->input, '\'')))
	{
		free(shell->waiting_char);
		shell->waiting_char = ft_char_to_str(shell->input[x]);
		ft_printd(0, "waiting %c\n", shell->waiting_char);
		ft_printd(0, "incomplete dquote situation\n");
		return (1);
	}
	return (0);
}

static int	_check_for_operators(t_shell *shell, int x)
{
	if (((shell->input[x] == '|') && (shell->input[x + 1] == 0))
		|| ((shell->input[x] == '&') && (shell->input[x + 1] == 0))
		|| ((shell->input[x] == '|') && (shell->input[x + 1] == '|')
			&& (shell->input[x + 2] == 0))
		|| ((shell->input[x] == '&') && (shell->input[x + 1] == '&')
			&& (shell->input[x + 2] == 0)))
	{
		return (1);
	}
	return (0);
}

static int	_is_not_complete(t_shell *shell)
{
	int		x;
	size_t	quote_cursor;

	x = -1;
	ft_printd(0, "_is_not_complete\n");
	while (shell->input[++x])
	{
		if (_check_for_operators(shell, x))
			return (1);
	}
	x = 0;
	while ((size_t)x <= ft_strlen(shell->input))
	{
		quote_cursor = x;
		if (_check_for_quotes(shell, x, &quote_cursor))
			return (1);
		x = quote_cursor + 1;
	}
	return (0);
}

int	_line_completion(t_shell *shell)
{
	char	*promptline;

	promptline = ft_strdup("");
	while (_is_not_complete(shell))
	{
		if (_open_new_prompt(shell, &promptline, FROM_PROMT))
		{
			ft_free(promptline);
			promptline = NULL;
			return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
		}
		shell->input = ft_strjoinfree(shell->input, ft_strdup(promptline));
		ft_free(promptline);
		promptline = ft_strdup("");
		free(shell->waiting_char);
		shell->waiting_char = ft_strdup("");
	}
	free(promptline);
	promptline = NULL;
	ft_printd(0, "exiting line_coimpletion\n");
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
