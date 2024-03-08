/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:40:02 by kzak              #+#    #+#             */
/*   Updated: 2022/12/28 13:36:10 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_home_path(t_shell *cd)
{
	char	*home_path;
	char	*error_string;

	error_string = NULL;
	home_path = msh_get_env_value(cd->envp, "HOME");
	if (home_path == NULL)
	{
		error_handler(1, ft_strdup("sushi: cd: HOME not set"), \
				DO_NOT_RESET);
	}
	else if (chdir(home_path) == -1)
	{
		error_string = ft_strjoinfree(ft_strdup("sushi: cd: "), \
			home_path);
		error_string = ft_strjoinfree(error_string, \
			ft_strdup(": No such file or directory"));
		error_handler(1, error_string, DO_NOT_RESET);
	}
	else if (chdir(home_path) != -1)
	{
		position(cd);
		free(home_path);
		error_handler(0, NULL, DO_NOT_RESET);
	}
}
