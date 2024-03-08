/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:27:38 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:28:37 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	error_directory(t_shell *shell, int index)
{
	char	*error_string;

	error_string = ft_strjoinfree(ft_strdup("sushi: "), \
		ft_strdup(shell->final_arguments[index]));
	error_string = ft_strjoinfree(error_string, \
		ft_strdup(": No such file or directory"));
	return (error_handler(127, error_string, DO_NOT_RESET));
}

static void	_error_assembly(char *name, int index)
{
	char	*error_string;

	if (index == 6)
	{
		error_string = ft_strjoinfree(ft_strdup(name), \
			ft_strdup(" Abort program: 6"));
	}
	if (index == 10)
	{
		error_string = ft_strjoinfree(ft_strdup(name), \
			ft_strdup(" Bus error: 10"));
	}
	if (index == 11)
	{
		error_string = ft_strjoinfree(ft_strdup(name), \
			ft_strdup(" Segmentation fault: 11"));
	}
	if (index == 15)
	{
		error_string = ft_strjoinfree(ft_strdup(name), \
			ft_strdup(" Terminated: 15"));
	}
	error_handler(index, error_string, DO_NOT_RESET);
}

void	_print_error_signaled(int signal, char *name)
{
	if (signal == SIGABRT)
		_error_assembly(name, 6);
	else if (signal == SIGBUS)
		_error_assembly(name, 10);
	else if (signal == SIGSEGV)
		_error_assembly(name, 11);
	else if (signal == SIGTERM)
		_error_assembly(name, 15);
}

int	signal_detected(t_shell *shell)
{
	if (WTERMSIG(g_exit_status) == 3)
	{
		return (error_handler(131, ft_strdup("Quit : 3"), \
			DO_NOT_RESET));
	}
	else if (WTERMSIG(g_exit_status) == 2)
		return (error_handler(130,
				ft_strdup(""), DO_NOT_RESET));
	if (shell->final_arguments)
		_print_error_signaled(WTERMSIG(g_exit_status), \
			shell->final_arguments[0]);
	else
		_print_error_signaled(WTERMSIG(g_exit_status), ft_strdup(""));
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}
