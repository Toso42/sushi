/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_logical_forker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:36:30 by tdi-leo           #+#    #+#             */
/*   Updated: 2023/01/03 16:57:11 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lforker.h"

static int	_evaluate_lastexit_and_operator(char *argument, int last_exit,
		int *lsplit_cursor, int *skip_flag)
{
	static int	waiting_for = 0;

	(void)lsplit_cursor;
	ft_printd(0, "assessing logical situation: {%s}\n waiting for = %d\n",
		argument, waiting_for);
	if (argument && is_and(argument[0]))
	{
		if (last_exit == EXITED_ERROR)
			return (EXIT_FAILURE);
		waiting_for = EXIT_SUCCESS;
	}
	else if (argument && is_or(argument[0]))
	{
		(*skip_flag) = 0;
		if (last_exit == EXITED_SUCCESS)
			return (EXIT_FAILURE);
		waiting_for = EXIT_FAILURE;
	}
	return (0);
}

static void	_ifoperator_execute(t_forker *v, t_shell *shell)
{
	if (v->lsplit_cursor == v->lsplit_size
		|| is_logical_operator(v->lsplit_cpy[v->lsplit_cursor]))
	{
		if (v->skip_flag == 0)
		{
			ft_printd(0, "this argument is operator (or last): {%s}\n",
				v->lsplit_cpy[v->lsplit_cursor]);
			ft_free(shell->input);
			shell->input = ft_strdup(v->rejoined_input);
			shell->passing_through_process = 0;
			ft_sarfree(shell->pipes_split, ft_sarsize(shell->pipes_split));
			shell->pipes_counter = 0;
			if (_lforker_sub_routine(shell))
				v->last_cmd_exit = EXITED_ERROR;
			else
				v->last_cmd_exit = EXITED_SUCCESS;
			if (v->last_cmd_exit == EXITED_ERROR)
				ft_printd(0, "last diverstion exited error\n");
		}
		ft_free(v->rejoined_input);
		v->rejoined_input = ft_strdup("");
	}
}

static void	_ifoperator_evaluate_execution(t_forker *v)
{
	if (v->lsplit_cursor
		&& (v->lsplit_cursor == v->lsplit_size
			|| is_logical_operator(v->lsplit_cpy[v->lsplit_cursor]))
		&& _evaluate_lastexit_and_operator(v->lsplit_cpy[v->lsplit_cursor],
			v->last_cmd_exit, &v->lsplit_cursor, &v->skip_flag))
	{
		v->skip_flag = 1;
		ft_printd(0, "__Last exit error {%d}\n", v->skip_flag);
	}
}

static void	_bufferize_the_rest(t_forker *v)
{
	if (v->lsplit_cpy[v->lsplit_cursor]
		&& !is_logical_operator(v->lsplit_cpy[v->lsplit_cursor]))
	{
		if (is_parenthesis(v->lsplit_cpy[v->lsplit_cursor][0]))
			_join_until_close_parenthesis(v);
		else
			v->rejoined_input = ft_strjoinfree(v->rejoined_input,
					ft_strdup(v->lsplit_cpy[v->lsplit_cursor]));
		ft_printd(0, "***after joining: {%s}\n", v->rejoined_input);
	}	
}

int	msh_logical_forker(t_shell *shell)
{
	t_forker	v;

	if (_init_forking(&v, shell))
		return (EXIT_SUCCESS);
	ft_printd(0, "inside logical forker\n");
	while (++v.lsplit_cursor <= v.lsplit_size)
	{
		ft_printd(0, "_entering round %d, arg: {%s}\n",
			v.lsplit_cursor, v.lsplit_cpy[v.lsplit_cursor]);
		_ifoperator_execute(&v, shell);
		_ifoperator_evaluate_execution(&v);
		_bufferize_the_rest(&v);
		ft_printd(0, "_exiting round %d, final rejoined input: {%s}\n",
			v.lsplit_cursor, v.rejoined_input);
	}
	ft_free(v.rejoined_input);
	ft_sarfree(v.lsplit_cpy, ft_sarsize(v.lsplit_cpy));
	ft_free(shell->input);
	shell->input = ft_strdup("");
	ft_printd(0, "exiting logical forker: {%s}\n", shell->input);
	shell->passing_through_process = 1;
	return (0);
}
