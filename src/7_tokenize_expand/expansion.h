/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:22:26 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 11:55:51 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "../minishell.h"

/* EXPANSION CASES */
int		_case_eof(t_splitter *v);
int		_case_dquote(t_splitter *v);
int		_case_squote(t_splitter *v);
int		_case_regular_separator(t_splitter *v);
int		_case_var(t_splitter *v);
int		_case_redirection(t_splitter *v);

/* HANDLERS */
int		spaces_handler(t_splitter *v);
int		handle_var(t_splitter *v);
int		_move_cursor_var_terminator(size_t *v, char *toparse);
void	_join_var_to_buffer(t_splitter *v, char *envp_match,
			char *var_expanded);
int		dquote_section_handler(t_splitter *v);
int		squote_section_handler(t_splitter *v);
//
int		msh_tokenize_expand(t_shell *shell);

#endif
