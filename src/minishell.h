/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:24:49 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 12:39:19 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*System library*/
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <dirent.h>

/*Readline library*/
# include "../readline/readline.h"
# include "../readline/history.h"

/*Program library*/
# include "types.h"
# include "../libft/libft.h"
# include "0_utils/mshutils.h"

/*Other headers*/
# include "0_splitting_utils/splitutils.h"
# include "1_prompt/prompt.h"
# include "2_syntax_splitter/s_splitter.h"
# include "3_syntax_parser/s_parser.h"
# include "4_logical_forker/lforker.h"
# include "5_pipes_splitter/p_splitter.h"
# include "6_pipes_forker/p_forker.h"
# include "7_tokenize_expand/expansion.h"
# include "8_namefile_expansion/wildcard.h"
# include "9_redirections/redirections.h"
# include "10_builtins/builtins.h"
# include "10_executor/executor.h"
/**/

# define EXIT_SHELL 42
# define ORANGE_C "\001\033[0;166m\002"
# define LGRAY_C "\001\033[0;37m\002"
# define ERROR_C "\001\033[0;31m\002"
# define GREEN_C "\001\033[0;32m\002"
# define YELLOW_C "\001\033[0;33m\002"
# define BLUE_C "\001\033[0;34m\002"
# define GRAY_C "\001\033[0;90m\002"
# define RESET_C "\001\033[0m\002"

/*Global variable*/
int	g_exit_status;

enum e_error_handler {
	ERHANLER_CAN_PRINT,
	ERHANLER_CANNOT_PRINT,
	RESET_ERRORHANDLER,
	RESET_PRINT,
	DO_NOT_RESET
};

enum e_redirection_types {
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_IN,
	REDIRECTION_HEREDOC,
	HEREDOC,
	FROM_PROMT
};

enum e_path_find {
	FOR_EXECVE,
	FOR_EXECUTOR
};

enum e_signals {
	MAIN_PROMPT,
	C_IGNORE,
	C_NO_NEWLINE,
	C_RESET,
	QUIT_IGNORE,
	QUIT_RESET
};

enum e_termios {
	TERMIOS_C_IGN,
	TERMIOS_C_DFL
};

enum e_access {
	READ_OK,
	WRITE_OK,
	EXEC_OK,
	EXIST_OK
} ;

enum e_logicwaiting {
	NOT_WAITING_YET,
	EXITED_SUCCESS,
	EXITED_ERROR
} ;

enum e_wildcard {
	EVERYWHERE,
	MUST_END,
	MUST_START,
	MUST_START_END,
	EVERY_EVERY,
	EVERY_MUST_END,
	MUST_START_EVERY,
	ALL_FILE
};

void	_reset_redirections(t_shell *shell);
int		error_handler(int errno, char *errmex, int flag_reset);
void	print_long_header(void);
void	print_short_header(void);

#endif
