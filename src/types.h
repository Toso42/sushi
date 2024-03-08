/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:24:55 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 11:01:12 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

typedef struct s_splitter
{
	char	**result;
	char	*input;
	char	*bufferline;
	char	**envp;
	size_t	cursor;
	size_t	old_cursor;
	size_t	nl_cursor;
	size_t	handling_dquote;
	int		old_exit_status;
}	t_splitter;

typedef struct s_wildcard
{
	char	**dir;
	char	**content_return;
	char	**w_a;
	char	*wild;
	int		wild_inside;
	int		tipe_wildcard;
	int		len_array;
}	t_wildcard;

typedef struct s_shell
{
	char	*input;
	char	*output;
	char	*process_description;
	char	*waiting_char;
	char	**envp;
	char	**pipes_split;
	char	**logical_split;
	char	**final_arguments;
	int		append_to_value;
	int		old_stdout;
	int		old_stdin;
	int		redirection_out;
	int		redirection_in;
	int		old_exit_status;
	int		process_level;
	int		passing_through_process;
	int		exit_shell;
	int		ctrld;
	size_t	pipes_counter;
	size_t	logical_counter;
	size_t	is_terminal_process;
}	t_shell;

typedef struct s_forker
{
	int		lsplit_cursor;
	int		lsplit_size;
	int		last_cmd_exit;
	int		skip_flag;
	char	*rejoined_input;
	char	**lsplit_cpy;
}	t_forker;

typedef struct s_heredoc
{
	char	**heredoc_complete;
	char	*heredoc_line;
	char	*heredoc_swap;
	int		stdout_swap;
	int		stdin_swap;
	int		line_counter;
}	t_heredoc;

#endif
