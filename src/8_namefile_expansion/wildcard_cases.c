/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:51:21 by kzak              #+#    #+#             */
/*   Updated: 2023/01/02 15:16:15 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	everywhere_case(t_wildcard *wildcard)
{
	int	cursor_content;

	cursor_content = -1;
	while (wildcard->dir[++cursor_content])
	{
		if (ft_strnstr(wildcard->dir[cursor_content], wildcard->wild,
				ft_strlen(wildcard->dir[cursor_content])))
			wildcard->content_return = ft_saradd_back(wildcard->content_return,
					wildcard->dir[cursor_content]);
	}
}

void	must_end_case(t_wildcard *wildcard)
{
	int	len;
	int	cursor_content;

	cursor_content = -1;
	len = 0;
	while (wildcard->dir[++cursor_content])
	{
		len = ft_strlen(wildcard->dir[cursor_content])
			- ft_strlen(wildcard->wild);
		if (len >= 0
			&& !ft_strncmp(&wildcard->dir[cursor_content][len],
			wildcard->wild, ft_strlen(wildcard->wild)))
			wildcard->content_return = ft_saradd_back(wildcard->content_return,
					wildcard->dir[cursor_content]);
	}
}

void	must_start_case(t_wildcard *wildcard)
{
	int	cursor_content;

	cursor_content = -1;
	while (wildcard->dir[++cursor_content])
	{
		if (!ft_strncmp(wildcard->dir[cursor_content], wildcard->wild,
				ft_strlen(wildcard->wild)))
			wildcard->content_return = ft_saradd_back(wildcard->content_return,
					wildcard->dir[cursor_content]);
	}
}

void	all_file_case(t_wildcard *wildcard)
{
	int	cursor_content;

	cursor_content = -1;
	while (wildcard->dir[++cursor_content])
	{
		if (ft_strncmp(wildcard->dir[cursor_content], ".", 1))
			wildcard->content_return = ft_saradd_back(wildcard->content_return,
					wildcard->dir[cursor_content]);
	}
}
