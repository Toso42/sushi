/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:15:29 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 16:53:25 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include "../minishell.h"
# define ERROR_MATCH "> sushi: unexpected EOF while looking for matching `"
# define ERROR_EOFN "'\nsushi: syntax error: unexpected end of file"
# define ERROR_EOF ">sushi: syntax error: unexpected end of file"

//msh_prompt
int		is_a_memorable_command(char *input);
int		msh_prompt(t_shell *shell);

//assemble_promptline
char	*assemble_prompt(t_shell *shell, int mode);

//line_completion
//int	_is_not_complete(t_shell *shell);
int		_line_completion(t_shell *shell);

//new_prompt
int		_open_new_prompt(t_shell *shell, char **promptline, int flag);

//sub_prompt
void	_sub_prompt(t_shell *shell, int *pipe_fd, int flag);

//prompt_utils
char	*current_dir_str(t_shell *shell);
char	*assemble_prompt(t_shell *shell, int mode);

#endif