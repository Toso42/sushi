/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:12:27 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 12:38:57 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# include "../minishell.h"

/*  HEREDOC  */
int		_spawn_and_print_heredoc(t_shell *shell, char *toprint);
int		_here_doc(t_shell *shell, int argument_cursor, char**heredoc_complete);

/* THIS IS ACTUALLY FROM TOKENIZE MODULE */
int		redirection_section_handler(t_splitter *v);
//resolve path
int		resolve_path(char *argument, int flag);
//
int		msh_redirection_handler(t_shell *shell);
#endif
