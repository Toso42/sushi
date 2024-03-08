/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:23:13 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:27:23 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	_add_value(t_shell *export, int env_pos, char *name, char *value)
{
	int		len_name;
	char	*temp_for_free;

	len_name = ft_strlen(name);
	if (!ft_strncmp(export->envp[env_pos], name, len_name) \
		&& (export->envp[env_pos][len_name] == '=' \
		|| export->envp[env_pos][len_name] == 0))
	{
		if (add_equal_plus(export, env_pos, len_name, value))
			return (1);
		temp_for_free = export->envp[env_pos];
		export->envp[env_pos] = ft_strjoin(name, "=");
		free(temp_for_free);
		if (value)
		{
			export->envp[env_pos] = \
				ft_strjoinfree(export->envp[env_pos], value);
		}
		return (1);
	}
	return (0);
}

static void	_check_and_format_value(t_shell *export, char *name, char *value)
{
	int		env_position;
	int		position_found;
	char	*temp_value;

	env_position = -1;
	temp_value = expand_value(value);
	while (export->envp[++env_position])
	{
		position_found = _add_value(export, env_position, name, temp_value);
		if (position_found)
			return ;
	}
}

static void	_add_it(t_shell *export, char **name_value, int name_len)
{
	if (name_value[0][name_len] == '+')
	{
		export->append_to_value = 1;
		name_value[0][name_len] = '\0';
	}
	if (!envar_strncmp(export, name_value[0]))
		if (!env_strcmp(export, name_value[0]))
			export->envp = ft_saradd_back(export->envp, name_value[0]);
	if (name_value[1])
		_check_and_format_value(export, name_value[0], name_value[1]);
}

static int	_add_var_to_env(t_shell *export)
{
	char	**name_value;
	int		argument;
	int		name_len;
	int		wrong_names;

	argument = 0;
	wrong_names = 0;
	while (export->final_arguments[++argument])
	{
		name_value = split_argument(export->final_arguments[argument], '=');
		name_len = ft_strlen(name_value[0]) - 1;
		if (name_value[0][0] == '\0')
			error_no_name(name_value, &wrong_names);
		else if (!validate_names(name_value[0], name_len, &wrong_names))
			_add_it(export, name_value, name_len);
		if (name_value)
			ft_sarfree(name_value, ft_sarsize(name_value));
	}
	if (wrong_names)
		return (error_handler(1, NULL, DO_NOT_RESET));
	else
		return (error_handler(0, NULL, DO_NOT_RESET));
}

int	export_command(t_shell *shell)
{
	int	status;

	shell->append_to_value = 0;
	if (shell->final_arguments[1])
	{
		status = _add_var_to_env(shell);
		return (error_handler(status, NULL, DO_NOT_RESET));
	}
	else
	{
		env_in_order(shell);
		return (error_handler(0, NULL, DO_NOT_RESET));
	}
}
