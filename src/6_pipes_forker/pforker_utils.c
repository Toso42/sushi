/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pforker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:28:53 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 12:36:50 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_forker.h"

void	_finalize(t_shell *shell, int pip_counter, int *pids,
		int last_process_flag)
{
	shell->pipes_counter = 0;
	while ((int)shell->pipes_counter < pip_counter)
	{
		_conditional_wait_forked_p(shell, pids[shell->pipes_counter],
			last_process_flag);
		shell->pipes_counter += 1;
	}
	free(pids);
	pids = NULL;
	ft_free(shell->process_description);
	shell->process_description = ft_strdup("Main process after pipe");
	shell->passing_through_process = 1;
}
