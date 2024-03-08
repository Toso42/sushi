/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:00:41 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:38:38 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printftypestring_fd(va_list args, char *ss, int sum, int fd)
{
	ss = va_arg(args, char *);
	if (ss == NULL)
		sum += ft_putstr_fd("(null)", fd);
	else if (ss != NULL)
		sum += ft_putstr_fd(ss, fd);
	return (sum);
}

// int	ft_putnmbu(unsigned int n, int sum)
// {
// 	if (n >= 10)
// 	{
// 		sum = ft_putnmbu((n / 10), sum);
// 		sum = ft_putnmbu((n % 10), sum);
// 	}
// 	else
// 		sum += ft_putchar(48 + n);
// 	return (sum);
// }

// int	ft_putnmbcx(unsigned int n, int sum, char *base)
// {
// 	if (n >= 16)
// 	{
// 		sum = ft_putnmbcx((n / 16), sum, base);
// 		sum = ft_putnmbcx((n % 16), sum, base);
// 	}
// 	else
// 		sum += ft_putchar(base[n]);
// 	return (sum);
// }

// int	ft_putnmbx(unsigned int n, int sum, char *base)
// {
// 	if (n >= 16)
// 	{
// 		sum = ft_putnmbx((n / 16), sum, base);
// 		sum = ft_putnmbx((n % 16), sum, base);
// 	}
// 	else
// 		sum += ft_putchar(base[n]);
// 	return (sum);
// }

// int	ft_putp(unsigned long long int n, int sum, char *base)
// {
// 	if (n >= 16)
// 	{
// 		sum = ft_putp((n / 16), sum, base);
// 		sum = ft_putp((n % 16), sum, base);
// 	}
// 	else
// 		sum += ft_putchar(base[n]);
// 	return (sum);
// }

// int	ft_padfd(unsigned long long int n, int sum, char *base, int fd)
// {
// 	write(fd, "0x", 2);
// 	sum += 2;
// 	sum = ft_putp(n, sum, base);
// 	return (sum);
// }
