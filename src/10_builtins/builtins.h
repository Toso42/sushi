/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:34 by kzak              #+#    #+#             */
/*   Updated: 2022/12/28 13:35:54 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

			/*BUILTINS*/
/*cd, cd_home_path*/
void	cd_home_path(t_shell *cd);
int		cd_command(t_shell *shell);
void	position(t_shell *cd);

/*echo*/
int		echo_command(char **str);

/*env*/
int		env_command(t_shell *env);

/*exit*/
int		exit_command(t_shell *shell);

/*export_sort*/
void	env_in_order(t_shell *export);

/*export_utils*/
int		validate_names(char *name, int name_len, int *wrong_names);
int		add_equal_plus(t_shell *export, int env_position, \
						int len_name, char *value);
char	*expand_value(char *value);
char	**split_argument(char *argument, char c);

/*export_utils2*/
void	error_no_name(char **name_value, int *wrong_names);

/*export*/
int		export_command(t_shell *shell);

/*pwd*/
int		pwd_command(void);

/*unset*/
int		unset_command(t_shell *shell);

/*utils_builtins*/
int		envar_strncmp(t_shell *builtins, char *to_compare);
int		env_strcmp(t_shell *builtins, char *to_compare);
int		env_strncmp(t_shell *shell, char *to_compare);
void	put_in_shell(t_shell *shell, t_shell *builtins);
void	put_in_builtins(t_shell *shell, t_shell *builtins);

#endif
