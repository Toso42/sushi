/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_splitter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:36:17 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/29 14:14:29 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_SPLITTER_H
# define P_SPLITTER_H
# include "../minishell.h"

int	_case_pipe(t_splitter *v);
int	_case_quote(t_splitter *v);
int	_case_pslit_parenthesis(t_splitter *v);

int	msh_pipes_splitter(t_shell *shell);

#endif
