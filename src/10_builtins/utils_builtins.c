/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:20:59 by kzak              #+#    #+#             */
/*   Updated: 2023/01/03 17:27:50 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	envar_strncmp(t_shell *builtins, char *to_compare)
{
	int	i;
	int	len;

	len = ft_strlen(to_compare);
	i = -1;
	while (builtins->envp[++i])
	{
		if (!ft_strncmp(builtins->envp[i], to_compare, len))
			if (builtins->envp[i][len] == '=' || builtins->envp[i][len] == '\0')
				return (1);
	}
	return (0);
}

/**
 * @brief env_strcmp search in the builtins->envp if exist the
 * string to_compare.
 * It use strcmp so it check if exist an identical to_compare
 * 
 * @param builtins structure
 * @param to_compare string to find in the envp
 * @return int It return 1 if it found a equal string.
 * Return 0 if nothing was found
 */
int	env_strcmp(t_shell *builtins, char *to_compare)
{
	int	i;

	i = -1;
	while (builtins->envp[++i])
	{
		if (!ft_strcmp(builtins->envp[i], to_compare))
			return (1);
	}
	return (0);
}

/**
 * @brief env_strncmp search in the shell->envp if exist the string to_compare.
 * It use strncmp so it check only for the leng of to_compare.
 * 
 * @param shell structure
 * @param to_compare string to find in the envp
 * @return int Ritorna 1 se trova una corrispondenza, 0 se non trova nulla
 */
int	env_strncmp(t_shell *shell, char *to_compare)
{
	int	i;
	int	len;

	if (!shell->envp)
		return (0);
	len = ft_strlen(to_compare);
	i = -1;
	while (shell->envp[++i])
	{
		if (!ft_strncmp(shell->envp[i], to_compare, len))
			return (1);
	}
	return (0);
}
