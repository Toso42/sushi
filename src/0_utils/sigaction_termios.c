/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction_termios.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:13:17 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 11:13:18 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

/**
 * @brief general function called to handle SigQuit.
 * 
 * @param sig_flag 
 */
void	sigquit_control(int sig_flag)
{
	struct sigaction	sg;

	if (sig_flag == QUIT_IGNORE)
	{
		sg.sa_handler = SIG_IGN;
	}
	else if (sig_flag == QUIT_RESET)
	{
		sg.sa_handler = SIG_DFL;
	}
	sg.sa_flags = SA_RESTART;
	sigemptyset(&sg.sa_mask);
	sigaction(SIGQUIT, &sg, NULL);
}

//main prompt : MAIN_PROMPT
void	display_newline(int signal)
{
	char	*nl;

	if (signal == SIGINT)
	{
		g_exit_status = 1;
		nl = assemble_prompt(NULL, 2);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_set_prompt(nl);
		rl_on_new_line();
		rl_redisplay();
		free(nl);
	}
}

//sub prompt : C_NO_NEWLINE
void	display_nothing(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

/**
 * @brief the general function called to control SigInt. To each flag
 * corresponds a different routine to be assigned the sa_Handler.
 * 
 * @param sig_flag 
 */
void	sigint_control(int sig_flag)
{
	struct sigaction	sg;

	if (sig_flag == MAIN_PROMPT)
	{
		sg.sa_handler = &display_newline;
	}
	else if (sig_flag == C_IGNORE)
	{
		sg.sa_handler = SIG_IGN;
	}
	else if (sig_flag == C_RESET)
	{
		sg.sa_handler = SIG_DFL;
	}
	else if (sig_flag == C_NO_NEWLINE)
	{
		sg.sa_handler = &display_nothing;
	}
	sigemptyset(&sg.sa_mask);
	sg.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sg, NULL);
}

/**
 * @brief This function flips the termios value for signal printing, 
 * and it does this through bitwise operations on the termios Masks. 
 * ae : {1 | 0 = 1}{*1 & 0 = 0 }{~1 = 0}{~0 = 1}{1 & ~1 = 0}
 * 
 * Similarly to Sigaction, a structore is contextually created
 * and modified, then fed to tcsetattr() function, which interacts
 * with the termios interface of the program.
 * TCSANOW attribute indicates the termios to make the above changes
 * immediatly.
 * @param echoctl_flag define if signals shall be printed or not by the
 * current terminal
 * @return int 
 */
int	set_termios(int echoctl_flag)
{
	struct termios	term;
	int				exit_status;

	exit_status = tcgetattr(STDOUT_FILENO, &term);
	if (exit_status == -1)
		return (-1);
	if (echoctl_flag)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	exit_status = tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	if (exit_status == -1)
		return (-1);
	return (0);
}
