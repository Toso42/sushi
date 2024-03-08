/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:45:58 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:32:55 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the character ’c’ to the given file
descriptor.
 * 
 * @param c 
 * @param fd 
 */
int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
