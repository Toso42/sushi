/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manipulation2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:47 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:10:04 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitutils.h"

/**
 * @brief this function splits the expanded var buffer and add them as final 
 * arguments one at a time.
 * 
 * @param v 
 * @return int 
 */
int	split_var_buffer(t_splitter *v)
{
	char	**bash_splitted_var;
	int		x;

	x = -1;
	bash_splitted_var = ft_split(v->bufferline, ' ');
	ft_printd(0, "Splittando la Var, risultato:\n");
	free(v->bufferline);
	while (++x < (ft_sarsize(bash_splitted_var) - 1))
	{
		v->bufferline = ft_strdup(bash_splitted_var[x]);
		add_buffer(v, 1);
	}
	v->bufferline = ft_strdup(bash_splitted_var[x]);
	ft_sarfree(bash_splitted_var, ft_sarsize(bash_splitted_var));
	return (EXIT_SUCCESS);
}

static char	**_remove_args_cases(t_splitter *v, char **trimmed_result, int x)
{
	ft_printd(0, "evaluating {%s}\n", v->result[x]);
	if ((ft_strlen(v->result[x]) > 1))
	{
		ft_printd(0, "_LONG ARGUMENT, ADDING AS A WHOLE {%s}:\n", \
		v->result[x]);
		trimmed_result = ft_saradd_back(trimmed_result, v->result[x]);
	}
	else if (ft_strlen(v->result[x]) == 1 && !is_space(v->result[x][0]))
		trimmed_result = ft_saradd_back(trimmed_result, v->result[x]);
	else if (v->result[x] && v->result[x][0] == '\0' && x != 0)
	{
		ft_printd(0, "adding a null argument:\n");
		trimmed_result = ft_saradd_back(trimmed_result, v->result[x]);
	}
	return (trimmed_result);
}

/**
 * @brief creates a new strings array excluding empty (" ") args.
 * 
 * @param splitted_args 
 * @return char** result
 */
int	remove_space_args(t_splitter *split_vars)
{
	char		**trimmed_result;
	int			x;
	t_splitter	*v;

	x = -1;
	trimmed_result = NULL;
	v = split_vars;
	if (!v->result)
		return (EXIT_SUCCESS);
	ft_printd(0, "REMOVING EMPTY ARGS\n");
	while (v->result[++x])
		trimmed_result = _remove_args_cases(v, trimmed_result, x);
	ft_sarfree(v->result, ft_sarsize(v->result));
	v->result = trimmed_result;
	ft_printd(0, "___REMOVE_SPACE_PRINT:\n");
	return (EXIT_SUCCESS);
}

static int	_move_cursor_loop(size_t *v, char *toparse, \
	size_t original_position, char tofind)
{
	while (toparse[v[0]])
	{
		ft_printd(0, "_ PARSING >{%c}\n", toparse[v[0]]);
		if (toparse[v[0]] == tofind)
		{
			ft_printd(0, "**next_occurrence found: {%d} {%c} returning\n", \
				v[0], toparse[v[0]]);
			return (EXIT_SUCCESS);
		}
		v[0] += 1;
	}
	v[0] = original_position;
	return (EXIT_FAILURE);
}

/**
 * @brief This function moves (*cursor) pointer in (*toparse) string,
 * until the next (tofind) char is found.
 * 
 * @param cursor 
 * @param toparse 
 * @param tofind 
 * @return int 
 */
int	move_cursor_next_occurrence(size_t *cursor, char *toparse, char tofind)
{
	size_t	*v;
	size_t	original_position;

	v = cursor;
	original_position = v[0];
	v[0] += 1;
	ft_printd(0, "** SEARCHING NEXT OCCURRENCE OF{%c} starting from: {%c}\n", \
		tofind, toparse[v[0]]);
	if (toparse[v[0]] == tofind)
		return (EXIT_SUCCESS);
	if (toparse[v[0]])
	{
		if (_move_cursor_loop(v, toparse, original_position, tofind))
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	v[0] = original_position;
	return (EXIT_FAILURE);
}
