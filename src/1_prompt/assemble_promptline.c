/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_promptline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:14:11 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/28 14:07:25 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*_regular_prompt(t_shell *shell_p, char *prompt,
	char *error, char *color)
{
	char	*current_dir;
	char	*sushi_color;
	char	*usr = msh_get_env_value(shell_p->envp, "USER");

	if (usr == NULL)
		usr = ft_strdup("");
	sushi_color = ft_strdup(GRAY_C"");
	current_dir = current_dir_str(shell_p);
	prompt = ft_strjoin(sushi_color, "[");
	prompt = ft_strjoinfree(prompt, strdup(color));
	prompt = ft_strjoinfree(prompt, error);
	prompt = ft_strjoinfree(prompt, strdup(sushi_color));
	prompt = ft_strjoinfree(prompt, ft_strdup("]sushi~["));
	prompt = ft_strjoinfree(prompt, strdup(color));
	prompt = ft_strjoinfree(prompt, usr);
	prompt = ft_strjoinfree(prompt, ft_strdup(sushi_color));
	prompt = ft_strjoinfree(prompt, ft_strdup("]["));
	prompt = ft_strjoinfree(prompt, ft_strdup(BLUE_C""));
	prompt = ft_strjoinfree(prompt, current_dir);
	prompt = ft_strjoinfree(prompt, strdup(sushi_color));
	prompt = ft_strjoinfree(prompt, ft_strdup("]: "));
	prompt = ft_strjoinfree(prompt, ft_strdup(RESET_C""));
	free(sushi_color);
	return (prompt);
}

static char	*_monocrome_prompt(t_shell *shell_p, char *prompt, char *error)
{
	prompt = ft_strjoinfree(ft_strdup("["), error);
	prompt = ft_strjoinfree(prompt, ft_strdup("]sushi~["));
	prompt = ft_strjoinfree(prompt, msh_get_env_value(shell_p->envp, "USER"));
	prompt = ft_strjoinfree(prompt, ft_strdup("]: "));
	return (prompt);
}

/**
 * @brief this function assembles the promptline to be fed to the readline.
 * 
 * @param shell 
 * @param mode 
 * @return char* 
 */
char	*assemble_prompt(t_shell *shell, int mode)
{
	static t_shell	*shell_p;
	char			*prompt;
	char			*color;
	char			*error;

	prompt = NULL;
	if (mode == 0)
	{
		shell_p = shell;
		return (NULL);
	}
	if (mode == 2 || mode == 3)
		error = ft_itoa(g_exit_status);
	else
		error = ft_itoa(shell_p->old_exit_status);
	if (shell_p->old_exit_status)
		color = ft_strdup(ERROR_C"");
	else
		color = ft_strdup(GREEN_C"");
	if (mode == 3)
		prompt = _monocrome_prompt(shell_p, prompt, error);
	else if (mode == 1 || mode == 2)
		prompt = _regular_prompt(shell_p, prompt, error, color);
	free(color);
	return (prompt);
}
