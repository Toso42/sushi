/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lforker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:53:20 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 11:55:15 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LFORKER_H
# define LFORKER_H
# include "../minishell.h"

//utils
int		_lforker_sub_routine(t_shell *shell);
int		_init_forking(t_forker *v, t_shell *shell);
//bufferization
char	*_join_until_close_parenthesis(t_forker *v);
//
int		msh_logical_forker(t_shell *shell);
#endif