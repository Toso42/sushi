/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection_splitter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:12:30 by kzak              #+#    #+#             */
/*   Updated: 2023/01/05 16:12:19 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

/**
 * @brief creates bufferline out of '\<' or '\>' chars. As soon as an
 * input[cursor] char invalidates the previous buffer as a valid
 * redirection argument, the buffer composing the valid argument so
 * far is added as an argument.
 * A new buffer is then created containing only the invalidating new
 * char and the loop is continued until a non \< \> char is found,
 * adding any residual buffer as final argument.
 * 
 * @param v 
 * @return int 
 */
static void	_creeting_buffer(t_splitter *v, char *oldarg_currentchar[2])
{
	char	*new_arg;

	new_arg = NULL;
	while (is_valid_redirection(oldarg_currentchar[0]))
	{
		v->cursor += 1;
		oldarg_currentchar[1] = ft_char_to_str(v->input[v->cursor]);
		if (!is_redirection(oldarg_currentchar[1][0]))
		{
			free(oldarg_currentchar[1]);
			oldarg_currentchar[1] = NULL;
			v->bufferline = oldarg_currentchar[0];
			break ;
		}
		new_arg = ft_strjoin(oldarg_currentchar[0], oldarg_currentchar[1]);
		free(oldarg_currentchar[1]);
		oldarg_currentchar[1] = NULL;
		if (!is_valid_redirection(new_arg))
		{
			free(new_arg);
			break ;
		}
		free(oldarg_currentchar[0]);
		oldarg_currentchar[0] = new_arg;
	}
}

int	redirection_section_handler(t_splitter *v)
{
	char	*oldarg_currentchar[2];

	oldarg_currentchar[0] = ft_char_to_str(v->input[v->cursor]);
	oldarg_currentchar[1] = NULL;
	_creeting_buffer(v, oldarg_currentchar);
	if (oldarg_currentchar[1])
	{
		free(oldarg_currentchar[1]);
		oldarg_currentchar[1] = NULL;
	}
	v->bufferline = oldarg_currentchar[0];
	if (is_valid_redirection(v->bufferline))
		add_buffer(v, 1);
	else
		free(v->bufferline);
	return (EXIT_SUCCESS);
}
