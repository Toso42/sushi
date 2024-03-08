/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:41 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:13:36 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitutils.h"

/**
 * @brief checks if bufferline exists; If not it creates one out of currend 
 * v.input[cursor], RETURNING 0.
 * If bufferline exist new_bufferline = (strjoin(bufferline, new_bufferline)), 
 * RETURNING 1.
 * @param v 
 * @param bufferline 
 * @param new_bufferline 
 * @return 0 bufferline didn't exist 1 new_bufferline created.
 */
int	new_or_join_buffer(t_splitter *v, char *bufferline, char *new_bufferline)
{
	char	*current_char;
	int		to_return;

	to_return = 0;
	(void)new_bufferline;
	current_char = NULL;
	ft_printd(0, ">> new_or_join called. bufferline: {%s}, new_bufferl {%s}\n",
		bufferline, new_bufferline);
	if (!bufferline)
	{
		bufferline = (char *)malloc(sizeof(char) * 2);
		bufferline[0] = v->input[v->cursor];
		bufferline[1] = 0;
		to_return = 0;
	}
	else
	{
		current_char = ft_strdup(" ");
		current_char[0] = v->input[v->cursor];
		new_bufferline = ft_strdup(ft_strjoinfree(bufferline, current_char));
		to_return = 1;
	}	
	ft_printd(0, ">> exiting new_or_join. bufferline: {%s}, new_bufferl {%s}\n",
		bufferline, new_bufferline);
	return (to_return);
}

/**
 * @brief creates a new shell.splitted_argument out of the whole bufferline.
 * It then procedes to free the bufferline. 
 * 
 * @param v 
 * @return int 
 */
int	add_buffer(t_splitter *v, int flag_newbuffer)
{
	ft_printd(0, "add_buffer called from {%c}\n", v->input[v->cursor -1]);
	if (!v->result && flag_newbuffer)
	{
		v->result = (char **)malloc(sizeof(char *));
		v->result[0] = NULL;
	}
	if (!v->bufferline && flag_newbuffer)
	{
		ft_printd(0, "Buffer non esiste\n");
		v->bufferline = ft_strdup("");
	}
	else
	{
		v->result = ft_saradd_back(v->result, v->bufferline);
		free(v->bufferline);
		v->bufferline = NULL;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief This function mallocates a new bufferline appending current char 
 * (input[cursor]) to the previous bufferline. It frees old bufferline.
 * if flag 1 is called, no v.input[cursor] character is joined to buffer.
 * @param v 
 * @return int 
 */
int	jointo_buffer(t_splitter *v, int flag)
{
	char	*character;

	character = NULL;
	if (!v->bufferline && v->input[v->cursor] != 0)
	{
		v->bufferline = (char *)malloc(sizeof(char));
		v->bufferline[0] = '\0';
	}
	if (v->bufferline)
	{
		if (flag == 0)
		{
			character = ft_substr(v->input, (v->cursor), 1);
			v->bufferline = ft_strjoinfree(v->bufferline, character);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief This function mallocates a new bufferline appending current char 
 * (input[cursor]) to the previous bufferline. It frees old bufferline.
 * 
 * @param v 
 * @return int 
 */
int	join_exit_status_to_buffer(t_splitter *v)
{
	char	*character;

	v->cursor += 1;
	if (!v->bufferline && v->input[v->cursor] == '?')
	{
		v->bufferline = ft_strdup(ft_itoa(v->old_exit_status));
	}
	else if (v->bufferline)
	{
		character = ft_strdup(ft_itoa(v->old_exit_status));
		v->bufferline = ft_strjoinfree(v->bufferline, character);
	}
	v->cursor += 1;
	if (is_regular_separator(v->input[v->cursor]))
		add_buffer(v, 0);
	return (EXIT_SUCCESS);
}
