/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:16 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 10:57:35 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PARSER_H
# define S_PARSER_H
# include "../minishell.h"

//handlers
int		_handle_open_parenthesis(t_shell *shell, int cursor);
int		_handle_close_parenthesis(t_shell *shell, int cursor);
int		_handle_operator(t_shell *shell, int cursor);
int		_handle_command(t_shell *shell, int cursor);
int		_handle_redirection(t_shell *shell, int cursor);

//cases
int		_case_parsing_operator(t_shell *shell, int cursor);
int		_case_parsing_parenthesis(t_shell *shell, int cursor);
int		_case_parsing_redirection(t_shell *shell, int cursor);
int		_case_parsing_command(t_shell *shell, int cursor);

//parser
int		is_invalid_redirection_arg(char *token);
char	*assemble_error(int flag, t_shell *shell, int cursor);
int		msh_syntax_parser(t_shell *shell);
#endif
