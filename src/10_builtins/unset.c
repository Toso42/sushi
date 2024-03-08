/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:21:39 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:27:37 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	_unset_it(t_shell *unset, int env_position)
{
	char	**new_env;
	int		line_in_env;
	int		line_in_new_env;
	int		len_envp;

	line_in_env = -1;
	line_in_new_env = 0;
	len_envp = ft_sarsize(unset->envp);
	new_env = (char **)malloc(sizeof(char *) * (len_envp));
	if (!new_env)
		return (0);
	while (unset->envp[++line_in_env] && line_in_env < len_envp)
	{
		if (line_in_env != env_position)
			new_env[line_in_new_env++] = ft_strdup(unset->envp[line_in_env]);
	}
	new_env[line_in_new_env] = NULL;
	ft_sarfree(unset->envp, ft_sarsize(unset->envp));
	unset->envp = new_env;
	return (1);
}

int	unset_command(t_shell *shell)
{
	int			env_position;
	int			argument;
	int			len_argument;

	argument = 0;
	while (shell->final_arguments[++argument])
	{
		env_position = -1;
		len_argument = ft_strlen(shell->final_arguments[argument]);
		while (shell->envp[++env_position])
		{
			if (!ft_strncmp(shell->envp[env_position], \
				shell->final_arguments[argument], len_argument) \
				&& (shell->envp[env_position][len_argument] == '=' \
				|| shell->envp[env_position][len_argument] == '\0'))
			{
				_unset_it(shell, env_position);
				break ;
			}
		}
	}
	return (error_handler(0, NULL, DO_NOT_RESET));
}
