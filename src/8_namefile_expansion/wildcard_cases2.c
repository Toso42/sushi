/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cases2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:58:43 by kzak              #+#    #+#             */
/*   Updated: 2023/01/02 15:54:04 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	must_start_end_case(t_wildcard *t_w)
{
	int		len;
	char	*temp_str;
	int		i;
	char	*cur_cont;

	cur_cont = NULL;
	i = -1;
	len = 0;
	temp_str = NULL;
	while (t_w->dir[++i])
	{
		len = ft_strlen(t_w->dir[i]) - ft_strlen(t_w->w_a[t_w->len_array - 1]);
		temp_str = ft_strnstr(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->dir[i]));
		if (!ft_strncmp(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->w_a[0]))
			&& len >= 0
			&& !ft_strncmp(&t_w->dir[i][len], t_w->w_a[t_w->len_array - 1],
			ft_strlen(t_w->w_a[t_w->len_array - 1])))
		{
			cur_cont = single_content(t_w, i, &temp_str[1]);
			t_w->content_return = ft_saradd_back(t_w->content_return, cur_cont);
			if (cur_cont)
				free(cur_cont);
		}
	}
}

void	every_every_case(t_wildcard *t_w)
{
	int		i;
	char	*temp_str;
	char	*cur_cont;

	cur_cont = NULL;
	i = -1;
	temp_str = NULL;
	while (t_w->dir[++i])
	{
		temp_str = ft_strnstr(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->dir[i]));
		if (ft_strnstr(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->dir[i])))
		{
			cur_cont = single_content(t_w, i, &temp_str[1]);
			t_w->content_return = ft_saradd_back(t_w->content_return, cur_cont);
			if (cur_cont)
				free(cur_cont);
		}
	}
}

void	every_must_end_case(t_wildcard *t_w)
{
	int		i;
	char	*temp_str;
	int		len;
	char	*cur_cont;

	cur_cont = NULL;
	len = 0;
	i = -1;
	temp_str = NULL;
	while (t_w->dir[++i])
	{
		len = ft_strlen(t_w->dir[i]) - ft_strlen(t_w->w_a[t_w->len_array - 1]);
		temp_str = ft_strnstr(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->dir[i]));
		if (len >= 0 && temp_str != NULL
			&& !ft_strncmp(&t_w->dir[i][len], t_w->w_a[t_w->len_array - 1],
			ft_strlen(t_w->w_a[t_w->len_array - 1])))
		{
			cur_cont = single_content(t_w, i, &temp_str[1]);
			t_w->content_return = ft_saradd_back(t_w->content_return, cur_cont);
			if (cur_cont)
				free(cur_cont);
		}
	}
}

void	must_start_every_case(t_wildcard *t_w)
{
	int		i;
	char	*temp_str;
	char	*cur_cont;

	cur_cont = NULL;
	i = -1;
	temp_str = NULL;
	while (t_w->dir[++i])
	{
		temp_str = ft_strnstr(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->dir[i]));
		if (!ft_strncmp(t_w->dir[i], t_w->w_a[0], ft_strlen(t_w->w_a[0])))
		{
			cur_cont = single_content(t_w, i, &temp_str[1]);
			t_w->content_return = ft_saradd_back(t_w->content_return, cur_cont);
			if (cur_cont)
				free(cur_cont);
		}
	}
}
