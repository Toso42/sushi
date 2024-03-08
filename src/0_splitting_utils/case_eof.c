/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_eof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:56:54 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/05 16:10:08 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitutils.h"

/**
 * @brief This is a generalized _case/handler specific for EOFs. If an END OF
 * FILE is found, buffer is joined to v.result (v is the struct used for splits) 
 * wholly.
 * 
 * @param v 
 * @return int 
 */
int	_case_eof(t_splitter *v)
{
	if (is_eof(v->input[v->old_cursor]))
	{
		ft_printd(0, "MANAGING CASE eof\n");
		ft_printd(0, "v.buffer: {%s}\n", v->bufferline);
		if (add_buffer(v, 0))
		{
			return (error_handler(0, ft_strdup("!!! _case_eof"), DO_NOT_RESET));
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
