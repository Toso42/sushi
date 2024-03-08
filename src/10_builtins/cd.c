/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:39:58 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:07 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	_update(t_shell *cd, int pwd, int old_pwd)
{
	char	*temp_for_free;
	char	*path;

	path = NULL;
	if (old_pwd >= 0 && pwd >= 0)
	{
		temp_for_free = cd->envp[old_pwd];
		cd->envp[old_pwd] = ft_strjoin("OLDPWD=", &cd->envp[pwd][4]);
		free(temp_for_free);
	}
	if (pwd >= 0)
	{
		temp_for_free = cd->envp[pwd];
		path = getcwd(path, PATH_MAX);
		cd->envp[pwd] = ft_strjoinfree(ft_strdup("PWD="), path);
		free(temp_for_free);
	}
}

void	position(t_shell *cd)
{
	int		old_pwd;
	int		pwd;
	int		env_position;

	env_position = -1;
	old_pwd = -1;
	pwd = -1;
	while (cd->envp[++env_position])
	{
		if (!ft_strncmp(cd->envp[env_position], "OLDPWD", 6))
			old_pwd = env_position;
		else if (!ft_strncmp(cd->envp[env_position], "PWD=", 4))
			pwd = env_position;
	}
	_update(cd, pwd, old_pwd);
}

static int	_cd_minus(t_shell *cd)
{
	char	**name_value;
	int		env_position;

	env_position = -1;
	if ((env_strcmp(cd, "OLDPWD") \
			&& !envar_strncmp(cd, "OLDPWD=")) \
			|| !envar_strncmp(cd, "OLDPWD"))
	{
		return (error_handler(1, \
			ft_strdup("sushi: cd: OLDPWD not set"), DO_NOT_RESET));
	}
	else if (envar_strncmp(cd, "OLDPWD"))
	{
		while (cd->envp[++env_position])
		{
			if (!ft_strncmp(cd->envp[env_position], "OLDPWD", 6))
			{
				name_value = ft_split(cd->envp[env_position], '=');
			}
		}
		ft_printf("%s\n", name_value[1]);
		ft_sarfree(name_value, ft_sarsize(name_value));
		return (error_handler(0, NULL, DO_NOT_RESET));
	}
	return (0);
}

int	_check_cd_argument(t_shell *shell)
{
	if (shell->final_arguments[1] && shell->final_arguments[2])
	{
		return (error_handler(1, ft_strdup(
					"sushi: cd: too many arguments"), DO_NOT_RESET));
	}
	else if (shell->final_arguments[1] && shell->final_arguments[1][0] == '\0')
		return (1);
	else if (!shell->final_arguments[1])
	{
		cd_home_path(shell);
		return (1);
	}
	return (0);
}

int	cd_command(t_shell *shell)
{
	char	*error_string;

	error_string = NULL;
	if (_check_cd_argument(shell))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	if (shell->final_arguments[1]
		&& !ft_strncmp(shell->final_arguments[1], "-", 2))
		return (error_handler(_cd_minus(shell), NULL, DO_NOT_RESET));
	else if (chdir(shell->final_arguments[1]) != -1)
	{
		position(shell);
		return (error_handler(0, NULL, DO_NOT_RESET));
	}
	else if (chdir(shell->final_arguments[1]) == -1)
	{
		error_string = ft_strjoinfree(ft_strdup("sushi: cd: "), \
			ft_strdup(shell->final_arguments[1]));
		error_string = ft_strjoinfree(error_string, \
			ft_strdup(": No such file or directory"));
		return (error_handler(1, error_string, DO_NOT_RESET));
	}
	return (error_handler(EXIT_SUCCESS, NULL, DO_NOT_RESET));
}
