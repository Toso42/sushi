/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lsplit_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:21:24 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:11:30 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_splitter.h"

static int	_split_loop_red(t_splitter *v, char **new_arg, char **old_arg)
{
	char	*current_char;

	v->cursor += 1;
	current_char = ft_char_to_str(v->input[v->cursor]);
	if (!is_redirection(current_char[0]))
	{
		free(current_char);
		current_char = NULL;
		v->bufferline = old_arg[0];
		return (1);
	}
	new_arg[0] = ft_strjoin(old_arg[0], current_char);
	free(current_char);
	current_char = NULL;
	if (!is_valid_redirection(new_arg[0]))
	{
		free(new_arg[0]);
		return (1);
	}
	ft_free(old_arg[0]);
	ft_free(current_char);
	old_arg[0] = new_arg[0];
	ft_printd(0, "exiting loop, [%d]\n", v->cursor);
	return (0);
}

static int	_split_loop_op(t_splitter *v, char **new_arg, char **old_arg)
{
	char	*current_char;

	v->cursor += 1;
	current_char = ft_char_to_str(v->input[v->cursor]);
	if (!is_operator(current_char[0]))
	{
		free(current_char);
		current_char = NULL;
		v->bufferline = old_arg[0];
		return (1);
	}
	new_arg[0] = ft_strjoin(old_arg[0], current_char);
	free(current_char);
	current_char = NULL;
	if (!is_valid_operator(new_arg[0]))
	{
		free(new_arg[0]);
		return (1);
	}
	ft_free(old_arg[0]);
	ft_free(current_char);
	old_arg[0] = new_arg[0];
	ft_printd(0, "exiting loop, [%d]\n", v->cursor);
	return (0);
}

/**
 * @brief Handler splitting the first whole redirection operator found.
 * 
 * @param v 
 * @return int 
 */
int	redirection_lsplit_handler(t_splitter *v)
{
	char	*new_arg;
	char	*old_arg;

	new_arg = NULL;
	old_arg = NULL;
	old_arg = ft_char_to_str(v->input[v->cursor]);
	ft_printd(0, "redirection section. First old arg: {%s} [%d]\n", old_arg,
		v->cursor);
	while (is_valid_redirection(old_arg)
		&& !_split_loop_red(v, &new_arg, &old_arg))
		;
	ft_printd(0, "out of loop, old_arg: {%s}\n", old_arg);
	v->bufferline = old_arg;
	if (is_valid_redirection(v->bufferline))
		add_buffer(v, 1);
	else
		free(v->bufferline);
	ft_printd(0, "exit redi_split, cursor is: {%d}, v.result so far:\n",
		v->cursor);
	return (EXIT_SUCCESS);
}

/**
 * @brief Handler splitting the first whole operator found.
 * 
 * @param v 
 * @return int 
 */
int	operator_lsplit_handler(t_splitter *v)
{
	char	*new_arg;
	char	*old_arg;

	new_arg = NULL;
	old_arg = NULL;
	old_arg = ft_char_to_str(v->input[v->cursor]);
	ft_printd(0, "operator section. First old arg: {%s}\n", old_arg);
	while (is_valid_operator(old_arg)
		&& !_split_loop_op(v, &new_arg, &old_arg))
		;
	ft_printd(0, "out of loop, old_arg: {%s}\n", old_arg);
	v->bufferline = old_arg;
	if (is_valid_operator(v->bufferline))
		add_buffer(v, 1);
	else
		free(v->bufferline);
	ft_printd(0, "exit split, cursor is: {%d}, v.result so far:\n",
		v->cursor);
	return (EXIT_SUCCESS);
}
