/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_forker.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:22:19 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/04 21:44:56 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_FORKER_H
# define P_FORKER_H
# include "../minishell.h"
//forked_pipes
int		_pipes_sub_routine(t_shell *shell);
int		subshell_fork(t_shell *shell, char *new_input);
char	*expand_parenthesis(t_shell *shell);
int		_prepare_struct_redirect_fd(t_shell *shell, int last_process_flag,
			int pipe_fd[2]);
//pipes_forker
int		search_parentheses_in_input(char *input);
int		_conditional_wait_forked_p(t_shell *shell, int pid,
			int last_process_flag);
int		msh_pipes_forker(t_shell *shell);
//utils
void	_finalize(t_shell *shell, int pip_counter, int *pids,
			int last_process_flag);
//compound commands
char	*_join_command_list(t_forker *v);
char	*compound_command_preparations(t_shell *shell);
void	_do_redirection(t_shell *shell, char *redirection);
#endif