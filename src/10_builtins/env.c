/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:23:53 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:17 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_command(t_shell *env)
{
	char	**temp_envp;
	char	*this_env;
	int		len_string;

	if (env->final_arguments[1])
		return (error_handler(1, ft_strdup(
					"sushi : env: parameters not implemented yet"),
				DO_NOT_RESET));
	temp_envp = ft_sarcopy(env->envp);
	while (*temp_envp != 0)
	{
		this_env = *temp_envp;
		len_string = ft_strlen(this_env);
		if (ft_strnstr(this_env, "=", len_string))
			ft_printf("%s\n", this_env);
		temp_envp++;
	}
	return (error_handler(0, NULL, DO_NOT_RESET));
}
