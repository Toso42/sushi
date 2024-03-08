/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:46:48 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 12:38:26 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../minishell.h"

/*wildcarc*/
void	init_t_wild(t_wildcard *wildcard, char *wild);

/*wildcard_do_wild*/
void	do_wildcard(t_wildcard *wildcard, char *wild);
char	*single_content(t_wildcard *wildcard, int cursor_content,
			char *temp_str);
int		all_file_check(char *wild, int len);

/*wildcard_cases*/
void	everywhere_case(t_wildcard *wildcard);
void	must_end_case(t_wildcard *wildcard);
void	must_start_case(t_wildcard *wildcard);
void	all_file_case(t_wildcard *wildcard);

/*wildcard_cases2*/
void	must_start_end_case(t_wildcard *wildcard);
void	every_every_case(t_wildcard *wildcard);
void	every_must_end_case(t_wildcard *wildcard);
void	must_start_every_case(t_wildcard *wildcard);
//
int		msh_namefile_expansion(t_shell *shell);

#endif
