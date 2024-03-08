/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_set_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:57:39 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/27 21:57:41 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshutils.h"

/**
 * @brief change cambia alcune righe della env per le nostre esigenze.
 * shlvl aumenta il livello di profondita' della minishell
 * 
 * @param shell structure
 * @param env la env che ci passa il pc
 * @param cursor_in_env la posizione, la riga nella env
 * @param index parametro che indica cosa cambiare
 */
static void	_change(t_shell *shell, char **env, int cursor_in_env, int index)
{
	char	*shlvl;

	if (index == 1)
	{
		shlvl = ft_itoa(ft_atoi(&env[cursor_in_env][6]) + 1);
		shlvl = ft_strjoinfree(ft_strdup("SHLVL="), shlvl);
		shell->envp = ft_saradd_back(shell->envp, shlvl);
		free(shlvl);
	}
	if (index == 2)
	{
		shell->envp = ft_saradd_back(shell->envp, "OLDPWD");
	}
	if (index == 3)
		shell->envp = ft_saradd_back(shell->envp, "SHELL=sushi");
}

/**
 * @brief set_env controlla se la riga della env corrisponde ad un
 * parametro che dobbiamo cambiare per necessita di programma.
 * Se si, le manda a _change, se no, copia da riga dalla env alla
 * nostra struttura.
 * 
 * @param shell structure
 * @param cursor_in_env riga nella quale ci troviamo nella env originale
 * @param env env passataci dal pc
 */
static void	_set_env(t_shell *shell, int cursor_in_env, char **env)
{
	if (!ft_strncmp("SHLVL=", env[cursor_in_env], 6))
		_change(shell, env, cursor_in_env, 1);
	else if (!ft_strncmp("OLDPWD=", env[cursor_in_env], 6))
		_change(shell, env, cursor_in_env, 2);
	else if (!ft_strncmp("SHELL=", env[cursor_in_env], 6))
		_change(shell, env, cursor_in_env, 3);
	else
		shell->envp = ft_saradd_back(shell->envp, env[cursor_in_env]);
}

/**
 * @brief copy_set_env passa a set_env la posizione della env del pc
 * e quella della nostra struttura shell->envp.
 * Aggiunge OLDPWD se non esiste nella env originale.
 * 
 * @param shell structure
 * @param env la env che ci passa il pc
 */
void	copy_set_env(t_shell *shell, char **env)
{
	int	len_env;
	int	cursor_in_env;

	cursor_in_env = -1;
	len_env = ft_sarsize(env);
	if (len_env != 0)
	{
		while (++cursor_in_env < len_env)
		{
			_set_env(shell, cursor_in_env, env);
		}
		if (!env_strncmp(shell, "OLDPWD"))
		{
			shell->envp = ft_saradd_back(shell->envp, "OLDPWD");
		}
		else
			shell->envp[cursor_in_env] = NULL;
	}
}
