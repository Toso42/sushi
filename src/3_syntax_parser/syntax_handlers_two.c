/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   syntax_handlers_two.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tdi-leo <tcorax42@gmail.com>			   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/29 10:50:02 by tdi-leo		   #+#	#+#			 */
/*   Updated: 2022/12/29 11:17:57 by tdi-leo		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "s_parser.h"

static void	_while_valid(t_shell *shell, int *cursor, int *operator_count)
{
	while (shell->logical_split[(*cursor)]
		&& (!is_command(shell->logical_split[(*cursor)])
			|| !is_valid_operator(shell->logical_split[(*cursor)])))
	{
		if (is_open_parenthesis(shell->logical_split[(*cursor)][0]))
			break ;
		if (is_valid_operator2(shell->logical_split[(*cursor)]))
		{
			++(*operator_count);
		}
		if (is_command(shell->logical_split[(*cursor)]))
		{
			ft_printd(0, "__command found: {%s}\n",
				shell->logical_split[(*cursor)]);
			break ;
		}
		++(*cursor);
	}
}

static int	_initial_checks(t_shell *shell, int *cursor, int split_size)
{
	if (split_size > 1)
	{
		if (shell->logical_split[(*cursor)][0] == '(')
		{
			return (error_handler(2, assemble_error(2, shell, cursor[0]),
					DO_NOT_RESET));
		}
	}
	return (0);
}

int	_handle_command(t_shell *shell, int cursor)
{
	char	**cmd_split;
	int		split_size;
	int		operator_count;

	operator_count = 0;
	cmd_split = ft_split(shell->logical_split[cursor], ' ');
	split_size = ft_sarsize(cmd_split);
	ft_sarfree(cmd_split, split_size);
	if (shell->logical_split[cursor][0] == ' ')
		split_size--;
	cursor++;
	if (!shell->logical_split[cursor])
		return (EXIT_SUCCESS);
	if (_initial_checks(shell, &cursor, split_size))
		return (error_handler(g_exit_status, NULL, DO_NOT_RESET));
	else
	{
		_while_valid(shell, &cursor, &operator_count);
		if (operator_count == 0 && shell->logical_split[cursor])
		{
			return (error_handler(2, assemble_error(2, shell, cursor),
					DO_NOT_RESET));
		}
	}
	return (EXIT_SUCCESS);
}

int	_handle_redirection(t_shell *shell, int cursor)
{
	if (is_invalid_redirection_arg(shell->logical_split[cursor + 1]))
	{
		return (error_handler(2, assemble_error(2, shell, (cursor + 1)),
				DO_NOT_RESET));
	}
	return (EXIT_SUCCESS);
}
