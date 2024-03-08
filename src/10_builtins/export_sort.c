/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:23:03 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:36 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	_print_with_quote(char *str)
{
	char	**name_value;
	char	double_quotes;

	double_quotes = 34;
	name_value = split_argument(str, '=');
	ft_printf("%s=%c%s%c\n", name_value[0], double_quotes, \
		name_value[1], double_quotes);
	ft_sarfree(name_value, ft_sarsize(name_value));
}

static char	**_sort(char **env)
{
	char	**temporary_env;
	int		env_position;
	int		next_env_position;
	int		compare_current_next;
	char	*temp_for_swap;

	env_position = -1;
	temporary_env = ft_sarcopy(env);
	while (temporary_env[++env_position])
	{
		next_env_position = env_position + 1;
		while (temporary_env[next_env_position])
		{
			compare_current_next = ft_strcmp(temporary_env[env_position], \
				temporary_env[next_env_position]);
			if (compare_current_next > 0)
			{
				temp_for_swap = temporary_env[env_position];
				temporary_env[env_position] = temporary_env[next_env_position];
				temporary_env[next_env_position] = temp_for_swap;
			}
			next_env_position++;
		}
	}
	return (temporary_env);
}

void	env_in_order(t_shell *export)
{
	char	**temporary_env;
	int		env_position;
	int		len_current_env;

	temporary_env = _sort(export->envp);
	env_position = -1;
	while (temporary_env[++env_position])
	{
		ft_printf("declare -x ");
		len_current_env = ft_strlen(temporary_env[env_position]);
		if (ft_strnstr(temporary_env[env_position], "=", len_current_env))
			_print_with_quote(temporary_env[env_position]);
		else
			ft_printf("%s\n", temporary_env[env_position]);
	}
	ft_sarfree(temporary_env, ft_sarsize(temporary_env));
}
