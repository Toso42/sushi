/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:27:02 by kzak              #+#    #+#             */
/*   Updated: 2022/12/28 11:27:24 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

			/*EXECUTOR*/
/*executor*/
int		msh_executor(t_shell *shell);

/*absolute_relative_path*/
int		is_absolute_path(t_shell *shell);
int		execute_absolute_path(t_shell *shell);

/*executor_utils*/
int		error_directory(t_shell *shell, int index);
int		signal_detected(t_shell *shell);

/*if_builtins*/
int		is_a_builtin(t_shell *shell);
int		execute_builtins(t_shell *shell);

/*relative_path*/
char	*is_a_program_name(t_shell *shell, int flag);
int		execute_program_name(t_shell *shell);

#endif
