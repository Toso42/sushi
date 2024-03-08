/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lforker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:45:15 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 14:57:20 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lforker.h"

/**
 * @brief If theres a logic evaluation betwean pipelines, this is the pipeline
 * track the pipeline will be diverted to.
 * 
 * @param shell 
 * @return int 
 */
int	_lforker_sub_routine(t_shell *shell)
{
	shell->passing_through_process = 0;
	error_handler(0, NULL, RESET_ERRORHANDLER);
	if (msh_pipes_splitter(shell)
		|| msh_pipes_forker(shell)
		|| msh_tokenize_expand(shell)
		|| msh_namefile_expansion(shell)
		|| msh_redirection_handler(shell)
		|| msh_executor(shell))
	{
		return (error_handler(g_exit_status, NULL, RESET_PRINT));
	}
	shell_partial_reset(shell);
	return (EXIT_SUCCESS);
}

int	_init_forking(t_forker *v, t_shell *shell)
{
	v->skip_flag = 0;
	if (shell->passing_through_process)
		return (EXIT_FAILURE);
	v->lsplit_cpy = ft_sarcopy(shell->logical_split);
	v->last_cmd_exit = 0;
	v->lsplit_size = ft_sarsize(v->lsplit_cpy);
	if (v->lsplit_size <= 1)
	{
		ft_printd(0, "Usciti logical_split {%d}\n", v->lsplit_size);
		ft_sarfree(v->lsplit_cpy, ft_sarsize(v->lsplit_cpy));
		return (EXIT_FAILURE);
	}
	v->rejoined_input = ft_strdup("");
	ft_printd(0, "entering logical forker.\n");
	v->lsplit_cursor = -1;
	return (EXIT_SUCCESS);
}
