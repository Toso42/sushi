/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:46:45 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/01/21 12:46:46 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary. Function returns void type.
 * 
 * @param *s string
 * @param (*f) function
 */
void	ft_striteri(char *s, void (*f) (unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != '\0')
	{
		f(i, (s + i));
		i++;
	}
}
