/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:22:21 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:26:51 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	add_equal_plus(t_shell *export, int env_position, \
					int len_name, char *value)
{
	char	*temp_for_free;

	if (export->envp[env_position][len_name] == 0)
	{
		temp_for_free = export->envp[env_position];
		export->envp[env_position] = \
			ft_strjoinfree(temp_for_free, ft_strdup("="));
	}
	if (export->append_to_value)
	{
		temp_for_free = export->envp[env_position];
		export->envp[env_position] = ft_strjoinfree(temp_for_free, value);
		return (1);
	}
	return (0);
}

int	validate_names(char *name, int name_len, int *wrong_names)
{
	int		cursor;
	char	*error_string;

	cursor = -1;
	while (name[++cursor])
	{
		if ((cursor == name_len) && (name[name_len] == '+'))
			break ;
		else if ((!ft_isalnum(name[cursor]) \
					&& name[cursor] != '_'\
					&& name[cursor] != '-'\
					&& name[cursor] != '=') \
					|| ft_isdigit(name[0]))
		{
			error_string = ft_strjoinfree(ft_strdup("sushi: export: `"), \
				ft_strdup(name));
			error_string = ft_strjoinfree(error_string, \
				ft_strdup("': not a valid identifier"));
			++(*wrong_names);
			return (error_handler(1, error_string, RESET_PRINT));
		}
	}
	return (0);
}

char	*expand_value(char *value)
{
	int		char_checking;
	int		value_len;
	char	*temp_value;

	char_checking = -1;
	temp_value = ft_strdup(value);
	value_len = ft_strlen(temp_value);
	while (++char_checking < value_len)
	{
		if (!is_an_acceptable_char(temp_value[char_checking]))
		{
			temp_value = ft_strintertrim(temp_value, temp_value[char_checking]);
			value_len = ft_strlen(temp_value);
			char_checking = -1;
		}
	}
	return (temp_value);
}

static char	**_creat_arguments(char *string, char separator, char **split_args)
{
	int	cursor;
	int	arg_counter;
	int	starting_point;
	int	find;

	find = 0;
	cursor = -1;
	arg_counter = 0;
	starting_point = 0;
	while (string[++cursor])
	{
		if (string[cursor] == separator && !find)
		{
			split_args[arg_counter] = ft_substr(string, starting_point, \
				(cursor - starting_point));
			starting_point = cursor + 1;
			arg_counter++;
			find = 1;
		}
	}
	split_args[arg_counter] = ft_substr(string, starting_point, \
		(cursor - starting_point));
	arg_counter++;
	split_args[arg_counter] = NULL;
	return (split_args);
}

char	**split_argument(char *argument, char c)
{
	char	**split_args;

	if (!argument)
		return (NULL);
	split_args = (char **) malloc (3 * sizeof(char *));
	if (!split_args)
		return (NULL);
	_creat_arguments(argument, c, split_args);
	return (split_args);
}
