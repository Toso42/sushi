/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:11:45 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 13:35:28 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*current_dir_str(t_shell *shell)
{
	char	*lastslash;
	char	*pwd;
	char	*current_dir;

	current_dir = NULL;
	pwd = msh_get_env_value(shell->envp, "PWD");
	lastslash = ft_strrchr(pwd, '/');
	current_dir = ft_strdup(lastslash);
	free(pwd);
	return (current_dir);
}
