/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:22:54 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/09 11:13:37 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief This function moves (*cursor) pointer in (*toparse) string, until a 
 * valid env_variable terminator is found. If not found, pointer is reset and 
 * function returns error.
 * 
 * @param v 
 * @param toparse 
 * @return int 
 */
int	_move_cursor_var_terminator(size_t *v, char *toparse)
{
	size_t	original_position;

	original_position = v[0];
	ft_printd(0, "_PARSING var name.\n");
	if (toparse[v[0]])
	{
		ft_printd(0, "__PARSING var name: {%c}\n", toparse[v[0]]);
		while (1)
		{
			if (is_var_terminator(toparse[v[0]]))
			{
				return (EXIT_SUCCESS);
			}
			v[0] += 1;
		}
		v[0] = original_position;
		ft_printd(0, "_NO VAR TERMINATOR\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

/**
 * @brief This function is called to expand a $variable found in shell.input.
 * The function joins the value to bufferline. If the variable doesnt expand, 
 * a NULL argument is joined. 
 * 
 * @param v 
 * @param envp_match 
 * @param var_expanded 
 */
void	_join_var_to_buffer(t_splitter *v, char *envp_match, char *var_expanded)
{
	size_t	env_cursor;

	env_cursor = 0;
	if (move_cursor_next_occurrence(&env_cursor, envp_match, '='))
		return ;
	env_cursor += 1;
	var_expanded = ft_substr(envp_match, env_cursor,
			(ft_strlen(envp_match) - env_cursor));
	ft_printd(0, "VAR_EXPANDED: {%s}\n", var_expanded);
	if (!v->bufferline)
		v->bufferline = ft_strdup("");
	v->bufferline = ft_strjoinfree(v->bufferline, var_expanded);
}

static int	_stupid_norm_trick(t_splitter *v, int utility_c, char *var_name)
{
	ft_free(var_name);
	v->cursor = utility_c;
	return (EXIT_SUCCESS);
}

/**
 * @brief This is the function to expand $env_vars and join them to bufferline. 
 * For Bash compliance, the bufferline is then splitted and joined accordingly.
 * 
 * @param v 
 * @return int 
 */
int	handle_var(t_splitter *v)
{
	size_t	utility_c;
	size_t	env_cursor;
	char	*var_name;
	char	*var_expanded;
	char	*envp_match;

	var_expanded = NULL;
	envp_match = NULL;
	var_name = NULL;
	v->cursor += 1;
	utility_c = v->cursor;
	env_cursor = -1;
	if (is_var(v->input[v->cursor]))
	{
		if (!v->bufferline)
			v->bufferline = ft_strdup("");
		v->bufferline = ft_strjoinfree(v->bufferline,
			ft_strdup(ft_itoa((int)getpid())));
		v->cursor += 2;
		return (_stupid_norm_trick(v, utility_c, var_name));
	}
	if (_move_cursor_var_terminator(&utility_c, v->input))
	{
		v->cursor -= 1;
		jointo_buffer(v, 0);
		v->cursor += 1;
		return (_stupid_norm_trick(v, utility_c, var_name));
	}
	if (v->cursor == utility_c)
	{
		if (!v->bufferline)
			v->bufferline = ft_strdup("");
		v->bufferline = ft_strjoinfree(v->bufferline, ft_strdup("$"));
		return (_stupid_norm_trick(v, utility_c, var_name));
	}
	var_name = ft_substr(v->input, v->cursor, (utility_c - v->cursor));
	ft_printd(1, "{%s}\n", var_name);
	while (!envp_match && v->envp[++env_cursor])
			envp_match = ft_strnstr_precision(v->envp[env_cursor], var_name,
					ft_strlen(var_name), '=');
	if (envp_match)
	{
		_join_var_to_buffer(v, envp_match, var_expanded);
		if (!v->handling_dquote && split_var_buffer(v))
			return (EXIT_FAILURE);
	}
	else
	{
		ft_printd(1, "dovrei essere qui\n");
		v->cursor -= 1;
		jointo_buffer(v, 0);
		v->cursor += 1;
	}
	return (_stupid_norm_trick(v, utility_c, var_name));
}

/**
 * @brief If a " " space argument is found, this function unloads buffer, 
 * create a new one_char buffer for the space, and then unloads the latter.
 * 
 * @param v 
 * @return int 
 */
int	spaces_handler(t_splitter *v)
{
	ft_printd(0, "_ADDING SEPARATOR\n");
	add_buffer(v, 0);
	ft_printd(0, "_ARGUMENTS AFTER SEP ADDITION:\n");
	v->cursor += 1;
	return (EXIT_SUCCESS);
}
