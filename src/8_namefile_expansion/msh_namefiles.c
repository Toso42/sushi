/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_namefiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:23:15 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 23:46:21 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static char	**_wildcard_expand(char	*wild)
{
	t_wildcard	wildcard;

	init_t_wild(&wildcard, wild);
	do_wildcard(&wildcard, wild);
	ft_sarfree(wildcard.dir, ft_sarsize(wildcard.dir));
	free(wildcard.wild);
	if (wildcard.w_a)
		ft_sarfree(wildcard.w_a, ft_sarsize(wildcard.w_a));
	return (wildcard.content_return);
}

static char	**_take_wildcard_expand(t_shell *shell, int cursor)
{
	char	**wild_expand;
	char	**temp_arg;
	int		i;

	i = -1;
	temp_arg = NULL;
	wild_expand = NULL;
	wild_expand = _wildcard_expand(shell->final_arguments[cursor]);
	if (wild_expand != NULL)
	{
		while (wild_expand[++i])
			temp_arg = ft_saradd_back(temp_arg, wild_expand[i]);
		ft_sarfree(wild_expand, ft_sarsize(wild_expand));
	}
	else
		temp_arg = ft_saradd_back(temp_arg,
				shell->final_arguments[cursor]);
	return (temp_arg);
}

static char	**_get_wildcard(t_shell *shell, int cursor)
{
	char	**temp_argument;

	temp_argument = NULL;
	if (ft_strnstr(shell->final_arguments[cursor], "*",
			ft_strlen(shell->final_arguments[cursor]))
		&& !ft_strnstr(shell->final_arguments[cursor], "/",
			ft_strlen(shell->final_arguments[cursor])))
	{
		temp_argument = _take_wildcard_expand(shell, cursor);
	}
	else
		temp_argument = ft_saradd_back(temp_argument,
				shell->final_arguments[cursor]);
	return (temp_argument);
}

int	msh_namefile_expansion(t_shell *shell)
{
	int		cursor;
	int		cursor_arg;
	char	**new_final_argument;
	char	**temp_argument;

	if (shell->passing_through_process || !shell->final_arguments)
		return (EXIT_SUCCESS);
	cursor = -1;
	cursor_arg = -1;
	temp_argument = NULL;
	new_final_argument = NULL;
	while (shell->final_arguments[++cursor])
	{
		temp_argument = _get_wildcard(shell, cursor);
		while (temp_argument[++cursor_arg])
			new_final_argument = ft_saradd_back(new_final_argument,
					temp_argument[cursor_arg]);
		ft_sarfree(temp_argument, ft_sarsize(temp_argument));
		cursor_arg = -1;
	}
	ft_sarfree(shell->final_arguments, ft_sarsize(shell->final_arguments));
	shell->final_arguments = new_final_argument;
	return (0);
}
