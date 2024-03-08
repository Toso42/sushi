/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:45:17 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 16:55:22 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	_sub_prompt_preparations(t_shell *shell, int *pipe_fd)
{
	sigint_control(C_NO_NEWLINE);
	set_termios(TERMIOS_C_DFL);
	shell->process_level += 1;
	free(shell->process_description);
	shell->process_description = ft_strdup("Created by msh_prompt");
	close(pipe_fd[0]);
}

static void	_sub_prompt_null_readline(t_shell *shell, char *readenline,
	int flag)
{
	if (flag == HEREDOC)
	{
		free(shell->waiting_char);
		shell->waiting_char = NULL;
		exit(142);
	}
	else if (shell->waiting_char[0] && flag == FROM_PROMT)
	{
		readenline = ft_strjoinfree(ft_strdup(ERROR_MATCH),
				shell->waiting_char);
		readenline = ft_strjoinfree(readenline, ft_strdup(ERROR_EOFN));
		shell->waiting_char = NULL;
		exit(error_handler(130, readenline, DO_NOT_RESET));
	}
	else
	{
		free(shell->waiting_char);
		shell->waiting_char = NULL;
		exit(error_handler(130, ft_strdup(ERROR_EOF), DO_NOT_RESET));
	}	
}

static void	_sub_prompt_graceful_exit(t_shell *shell, char **readenline,
	int *pipe_fd)
{
	ft_printd(0, "!_WARNING: prompt_exit non-null but empty buffer\n");
	free_and_exit(shell);
	close(pipe_fd[1]);
	ft_free(readenline[0]);
	ft_free(shell->waiting_char);
	shell->waiting_char = NULL;
	exit(EXIT_SUCCESS);
}

void	_sub_prompt(t_shell *shell, int *pipe_fd, int flag)
{
	char	*readenline;
	int		string_size;

	_sub_prompt_preparations(shell, pipe_fd);
	readenline = readline("> ");
	add_history(readenline);
	if (readenline == NULL)
		_sub_prompt_null_readline(shell, readenline, flag);
	string_size = ft_strlen(readenline);
	ft_printd(0, "string size %d\n", string_size);
	if (!string_size)
		write(pipe_fd[1], &string_size, sizeof(int));
	else
	{
		write(pipe_fd[1], &string_size, sizeof(int));
		write(pipe_fd[1], readenline, (sizeof(char) * string_size));
		write(pipe_fd[1], "\0", sizeof(char));
	}
	_sub_prompt_graceful_exit(shell, &readenline, pipe_fd);
}
