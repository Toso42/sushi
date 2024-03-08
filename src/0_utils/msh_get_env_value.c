/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:44 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 11:34:09 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

char	*msh_get_env_value(char **env, char *var_name)
{
	size_t	cursor;
	char	*var_pointer;
	char	*var_value;

	cursor = -1;
	var_pointer = NULL;
	var_value = NULL;
	ft_printd(0, "get_env_value called with {%s}\n", var_name);
	while (!var_pointer && env[++cursor])
		var_pointer = ft_strnstr_precision(env[cursor], \
		var_name, ft_strlen(var_name), '=');
	if (!var_pointer)
	{
		ft_printd(0, "no pointer found\n");
		return (NULL);
	}
	cursor = 0;
	move_cursor_next_occurrence(&cursor, var_pointer, '=');
	cursor++;
	var_value = ft_substr(var_pointer, cursor, \
	(ft_strlen(var_pointer) - cursor));
	return (var_value);
}
