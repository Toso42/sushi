/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:54:38 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 21:43:28 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_forker.h"

char	*_join_command_list(t_forker *v)
{
	char	*redirection;

	redirection = ft_strdup("");
	v->rejoined_input = ft_strdup("");
	if (!v->lsplit_cpy)
	{
		return (redirection);
	}
	while (v->lsplit_cpy[++v->lsplit_cursor])
	{
		if (is_open_parenthesis(v->lsplit_cpy[v->lsplit_cursor][0]))
		{
			_join_until_close_parenthesis(v);
			break ;
		}
	}
	while (v->lsplit_cpy[++v->lsplit_cursor])
		redirection = ft_strjoinfree(redirection,
				ft_strdup(v->lsplit_cpy[v->lsplit_cursor]));
	ft_printd(0, "compound command {%s} redirection {%s}\n",
		v->rejoined_input, redirection);
	return (redirection);
}

void	_do_redirection(t_shell *shell, char *redirection)
{
	if (!redirection || (redirection && !ft_strlen(redirection)))
		return ;
	ft_printd(0, "theres a redirection\n");
	ft_free(shell->input);
	shell->input = ft_strdup(redirection);
	msh_tokenize_expand(shell);
	msh_redirection_handler(shell);
	ft_printd(0, "this should not print\n");
}

char	*compound_command_preparations(t_shell *shell)
{
	t_shell		utility_shell;
	t_forker	v;
	char		*eventual_redirection;

	ft_printd(0, "compounds preparations on: {%s}\n", shell->input);
	if (!shell->input)
		return (NULL);
	init_shell(&utility_shell);
	utility_shell.input = ft_strdup(shell->input);
	msh_syntax_splitter(&utility_shell);
	v.lsplit_cpy = utility_shell.logical_split;
	v.lsplit_cursor = -1;
	eventual_redirection = _join_command_list(&v);
	_do_redirection(&utility_shell, eventual_redirection);
	ft_printd(0, "also this should not print\n");
	free(eventual_redirection);
	shell_partial_reset(&utility_shell);
	ft_free(utility_shell.input);
	utility_shell.input = v.rejoined_input;
	v.rejoined_input = expand_parenthesis(&utility_shell);
	free_and_exit(&utility_shell);
	return (v.rejoined_input);
}
