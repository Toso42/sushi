/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_splitter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:21:46 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 21:00:45 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SPLITTER_H
# define S_SPLITTER_H
# include "../minishell.h"

int	_case_parenthesis(t_splitter *v);
int	_case_operator(t_splitter *v);
int	_case_quote(t_splitter *v);
int	_case_l_redirection(t_splitter *v);

//handlers
int	operator_lsplit_handler(t_splitter *v);
int	redirection_lsplit_handler(t_splitter *v);

int	msh_syntax_splitter(t_shell *shell);
#endif