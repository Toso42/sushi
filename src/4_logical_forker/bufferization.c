/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tdi-leo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:52:13 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/02 16:41:32 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lforker.h"

static void	_join_and_count(int *tocount, t_forker *v)
{
	if (tocount)
		tocount[0]++;
	v->rejoined_input = ft_strjoinfree(v->rejoined_input,
			ft_strdup(v->lsplit_cpy[v->lsplit_cursor]));
}

char	*_join_until_close_parenthesis(t_forker *v)
{
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (v->lsplit_cpy[v->lsplit_cursor])
	{
		ft_printd(0, "loop start: arg {%s}, joined: {%s}\n",
			v->lsplit_cpy[v->lsplit_cursor], v->rejoined_input);
		if (is_open_parenthesis(v->lsplit_cpy[v->lsplit_cursor][0]))
			_join_and_count(&open, v);
		else if (is_close_parenthesis(v->lsplit_cpy[v->lsplit_cursor][0]))
			_join_and_count(&close, v);
		else
			_join_and_count(NULL, v);
		v->lsplit_cursor++;
		if (open == close)
			break ;
		ft_printd(0, "loop end: arg {%s}, joined: {%s}\n",
			v->lsplit_cpy[v->lsplit_cursor], v->rejoined_input);
	}
	v->lsplit_cursor--;
	ft_printd(0, "***after joining: {%s}\n", v->rejoined_input);
	return (v->rejoined_input);
}
