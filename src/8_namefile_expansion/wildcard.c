/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:51:23 by kzak              #+#    #+#             */
/*   Updated: 2023/01/02 15:53:12 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	_check_wildcard_type(char *wild, int wild_inside)
{
	int	len;

	len = ft_strlen(wild);
	if (all_file_check(wild, len))
		return (ALL_FILE);
	else if (ft_strncmp(wild, "*", 1) && ft_strncmp(&wild[len - 1], "*", 1))
		return (MUST_START_END);
	else if (!ft_strncmp(wild, "*", 1) && !ft_strncmp(&wild[len - 1], "*", 1)
		&& wild_inside == 1)
		return (EVERY_EVERY);
	else if (!ft_strncmp(wild, "*", 1) && ft_strncmp(&wild[len - 1], "*", 1)
		&& wild_inside == 1)
		return (EVERY_MUST_END);
	else if (ft_strncmp(wild, "*", 1) && !ft_strncmp(&wild[len - 1], "*", 1)
		&& wild_inside == 1)
		return (MUST_START_EVERY);
	else if (!ft_strncmp(wild, "*", 1) && !ft_strncmp(&wild[len - 1], "*", 1))
		return (EVERYWHERE);
	else if (!ft_strncmp(wild, "*", 1))
		return (MUST_END);
	else if (!ft_strncmp(&wild[len - 1], "*", 1))
		return (MUST_START);
	return (0);
}

static int	_check_wild_inside(char *wild)
{
	int	i;

	i = 0;
	while (wild[i] == 42)
		i++;
	while (wild[i])
	{
		if (wild[i] == 42 && wild[i + 1] != 42 && wild[i + 1] != 0)
			return (1);
		i++;
	}
	return (0);
}

static char	**_remove_point(char **dir_content)
{
	int		i;
	char	**real_content;

	i = -1;
	real_content = NULL;
	while (dir_content[++i])
	{
		if (ft_strncmp(dir_content[i], ".", 1)
			&& ft_strncmp(dir_content[i], "..", 2))
		{
			real_content = ft_saradd_back(real_content, dir_content[i]);
		}
	}
	return (real_content);
}

static char	**_get_dir_content(void)
{
	struct dirent	*dir;
	DIR				*directory;
	char			actual_path[PATH_MAX];
	char			**dir_contents;
	char			**real_content;

	real_content = NULL;
	dir_contents = NULL;
	directory = opendir(getcwd(actual_path, sizeof(actual_path)));
	dir = readdir(directory);
	while (dir)
	{
		dir_contents = ft_saradd_back(dir_contents, dir->d_name);
		dir = readdir(directory);
	}
	closedir(directory);
	real_content = _remove_point(dir_contents);
	ft_sarfree(dir_contents, ft_sarsize(dir_contents));
	return (real_content);
}

void	init_t_wild(t_wildcard *wildcard, char *wild)
{
	wildcard->dir = _get_dir_content();
	wildcard->content_return = NULL;
	wildcard->w_a = NULL;
	wildcard->wild = ft_strdup(wild);
	wildcard->wild_inside = _check_wild_inside(wild);
	wildcard->tipe_wildcard = _check_wildcard_type(wild, wildcard->wild_inside);
	wildcard->len_array = 0;
}
