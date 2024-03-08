/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_do_wild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:56:27 by kzak              #+#    #+#             */
/*   Updated: 2023/01/02 15:55:00 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	all_file_check(char *wild, int len)
{
	int	cursor;

	cursor = -1;
	while (wild[++cursor])
		if (wild[cursor] != 42)
			break ;
	if (cursor == len)
		return (1);
	return (0);
}

char	*single_content(t_wildcard *wildcard, int cursor_content,
		char *temp_str)
{
	char	*content_found;
	int		to_len_array;

	to_len_array = 0;
	content_found = NULL;
	while (++to_len_array != wildcard->len_array)
	{
		if (ft_strnstr(temp_str, wildcard->w_a[to_len_array],
				ft_strlen(temp_str)))
			temp_str = ft_strnstr(temp_str, wildcard->w_a[to_len_array],
					ft_strlen(temp_str));
		else
			break ;
		if (to_len_array == wildcard->len_array - 1)
			content_found = ft_strdup(wildcard->dir[cursor_content]);
	}
	return (content_found);
}

static void	_split_wildcard_argument(t_wildcard *wildcard, char *wild)
{
	int	pass_first_wild;

	pass_first_wild = 0;
	while (wild[pass_first_wild] == 42)
		pass_first_wild++;
	wildcard->w_a = ft_split(&wild[pass_first_wild], '*');
	wildcard->len_array = ft_sarsize(wildcard->w_a);
}

void	do_wildcard(t_wildcard *wildcard, char *wild)
{
	if (wildcard->tipe_wildcard > 2)
		_split_wildcard_argument(wildcard, wild);
	else
		wildcard->wild = ft_strintertrim(wildcard->wild, '*');
	if (wildcard->tipe_wildcard == ALL_FILE)
		all_file_case(wildcard);
	else if (wildcard->tipe_wildcard == EVERYWHERE)
		everywhere_case(wildcard);
	else if (wildcard->tipe_wildcard == MUST_END)
		must_end_case(wildcard);
	else if (wildcard->tipe_wildcard == MUST_START)
		must_start_case(wildcard);
	else if (wildcard->tipe_wildcard == MUST_START_END)
		must_start_end_case(wildcard);
	else if (wildcard->tipe_wildcard == EVERY_EVERY)
		every_every_case(wildcard);
	else if (wildcard->tipe_wildcard == EVERY_MUST_END)
		every_must_end_case(wildcard);
	else if (wildcard->tipe_wildcard == MUST_START_EVERY)
		must_start_every_case(wildcard);
}
