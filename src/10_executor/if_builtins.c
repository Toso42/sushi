/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:32:02 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:29:04 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_a_builtin(t_shell *shell)
{
	if ((ft_strncmp(shell->final_arguments[0], "echo", 5) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "cd", 3) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "pwd", 4) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "export", 7) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "unset", 6) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "env", 4) == 0)
		|| (ft_strncmp(shell->final_arguments[0], "exit", 5) == 0))
		return (1);
	return (0);
}

int	execute_builtins(t_shell *shell)
{
	if (((ft_strncmp(shell->final_arguments[0], "echo", 5) == 0)
			&& echo_command(shell->final_arguments))
		|| ((ft_strncmp(shell->final_arguments[0], "cd", 3) == 0)
			&& cd_command(shell))
		|| ((ft_strncmp(shell->final_arguments[0], "pwd", 4) == 0)
			&& pwd_command())
		|| ((ft_strncmp(shell->final_arguments[0], "export", 7) == 0)
			&& export_command(shell))
		|| ((ft_strncmp(shell->final_arguments[0], "unset", 6) == 0)
			&& unset_command(shell))
		|| ((ft_strncmp(shell->final_arguments[0], "env", 4) == 0)
			&& env_command(shell))
		|| ((ft_strncmp(shell->final_arguments[0], "exit", 5) == 0
				&& exit_command(shell))))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	return (0);
}
