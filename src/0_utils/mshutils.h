/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:50 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 12:19:31 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHUTILS_H
# define MSHUTILS_H

# include "../minishell.h"

			/*UTILS*/

//general_case_handling
int		_case_eof(t_splitter *v);
int		handle_exit_status(t_splitter *v);
//cursor_handling
int		move_cursor_next_occurrence(size_t *cursor, char *toparse, char tofind);

/*char _checks*/
int		is_var(char c);
int		is_squote(char c);
int		is_dquote(char c);
int		is_space(char c);
int		is_eof(char c);

/*char_checks2*/
int		is_symbol_separator(char c);
int		is_var_terminator(char c);

int		is_pipe(char c);
int		is_redirection(char c);
int		is_operator(char c);

/*char_check3*/
int		is_an_acceptable_char(char c);
int		is_regular_separator(char c);
int		is_parenthesis(char c);
int		is_and(char c);
int		is_or(char c);

/*char_checks4*/
int		is_open_parenthesis(char c);
int		is_close_parenthesis(char c);

/*str_checks*/
int		is_valid_pipe(char *arg);
int		is_valid_operator(char *p);
int		is_valid_redirection(char *arg);
int		is_command(char *token);
int		is_logical_operator(char *arg);

/*str_checks2*/
int		is_valid_operator2(char *arg);

/*copy_set_env*/
void	copy_set_env(t_shell *shell, char **env);

/*msh_get_env_value*/
char	*msh_get_env_value(char **env, char *var_name);

/*shell_handling*/
void	init_shell(t_shell *shell);
void	shell_reset(t_shell *shell);
int		free_and_exit(t_shell *shell);
void	shell_partial_reset(t_shell *shell);

/*termios_sigaction*/
int		set_termios(int echoctl_flag);
void	sigint_control(int sig_flag);
void	sigquit_control(int sig_flag);

#endif
