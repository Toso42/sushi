/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_red_resolvepath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:12:38 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:25:29 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

static int	_join_error(char *argument, int flag)
{
	char	*error_string;

	error_string = ft_strjoinfree(ft_strdup("sushi: "), \
		ft_strdup(argument));
	if (flag == EXIST_OK)
		error_string = ft_strjoinfree(error_string, \
		ft_strdup(": No such file or directory"));
	else if (flag == READ_OK)
		error_string = ft_strjoinfree(error_string, \
		ft_strdup(": Permission denied"));
	else if (flag == WRITE_OK)
		error_string = ft_strjoinfree(error_string, \
		ft_strdup(": Permission denied"));
	else if (flag == EXEC_OK)
		error_string = ft_strjoinfree(error_string, \
		ft_strdup(": Permission denied"));
	return (error_handler(1, error_string, DO_NOT_RESET));
}

static int	_access_control(char *path_file, char *argument,
	int flag, int to_free)
{
	if (access(path_file, F_OK))
		g_exit_status = _join_error(argument, EXIST_OK);
	if (flag == READ_OK
		&& access(path_file, R_OK))
			g_exit_status = _join_error(argument, READ_OK);
	else if (flag == WRITE_OK
		&& access(path_file, W_OK))
			g_exit_status = _join_error(argument, WRITE_OK);
	else if (flag == EXEC_OK
		&& access(path_file, X_OK))
			g_exit_status = _join_error(argument, EXEC_OK);
	if (to_free == 1)
		free(path_file);
	return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
}

static int	_is_absolute_path(char *argument)
{
	if (ft_strnstr(argument, "/", 1))
		return (1);
	return (0);
}

int	resolve_path(char *argument, int flag)
{
	char	*actual_path;
	char	*path_file;

	actual_path = NULL;
	path_file = NULL;
	actual_path = getcwd(actual_path, PATH_MAX);
	path_file = ft_strjoin(actual_path, "/");
	path_file = ft_strjoinfree(path_file, ft_strdup(argument));
	if (_is_absolute_path(argument))
	{
		_access_control(argument, argument, flag, 0);
		free(path_file);
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	}
	if (_access_control(path_file, argument, flag, 1))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	return (g_exit_status);
}
