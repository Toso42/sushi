/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitutils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:59 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:11:16 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITUTILS_H
# define SPLITUTILS_H
# include "../minishell.h"

int	new_or_join_buffer(t_splitter *v, char *bufferline, char *new_bufferline);
int	add_buffer(t_splitter *v, int flag_newbuffer);
int	jointo_buffer(t_splitter *v, int flag);
int	join_exit_status_to_buffer(t_splitter *v);

int	split_var_buffer(t_splitter *v);
int	remove_space_args(t_splitter *split_vars);
int	move_cursor_next_occurrence(size_t *cursor, char *toparse, char tofind);

int	_case_eof(t_splitter *v);
#endif