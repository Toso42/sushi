/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:47:07 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:39:53 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static int	ft_typefd(va_list args, const char *string, int sum, int fd_x[2])
{
	char	*local_string;

	local_string = NULL;
	(void)local_string;
	(void)args;
	if (string[fd_x[1]] == 'c')
		sum += ft_putchar_fd(va_arg(args, int), fd_x[0]);
	else if (string[fd_x[1]] == 's')
	{
		local_string = ft_strdup(va_arg(args, char *));
		sum += ft_putstr_fd(local_string, fd_x[0]);
		free(local_string);
	}
	else if (string[fd_x[1]] == 'd' || string[fd_x[1]] == 'i')
	{
		local_string = ft_itoa(va_arg(args, int));
		sum += ft_strlen(local_string);
		ft_putstr_fd(local_string, fd_x[0]);
		free(local_string);
	}
	return (sum);
}

int	ft_printfd(int fd, const char *string, ...)
{
	int		sum;
	va_list	args;
	int		fd_x[2];

	va_start(args, string);
	fd_x[0] = fd;
	fd_x[1] = 0;
	sum = 0;
	while (string[fd_x[1]] != 0)
	{
		if (string[fd_x[1]] == '%')
		{
			fd_x[1] += 1;
			sum = ft_typefd(args, string, sum, fd_x);
		}
		else
		{
			ft_putchar_fd(string[fd_x[1]], fd_x[0]);
			sum += 1;
		}
		fd_x[1] += 1;
	}
	va_end(args);
	return (sum);
}
