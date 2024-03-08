/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:46:18 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:32:31 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the string ’s’ to the given file
descriptor.
 * 
 * @param s 
 * @param fd 
 */
int	ft_putstr_fd(char *s, int fd)
{
	int	x;

	x = 0;
	if (s == NULL)
		return (0);
	while (s[x])
	{
		write(fd, &s[x], 1);
		x++;
	}
	return (x);
}
