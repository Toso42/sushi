/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:00:41 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/03/28 19:04:40 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnmbu(unsigned int n, int sum)
{
	if (n >= 10)
	{
		sum = ft_putnmbu((n / 10), sum);
		sum = ft_putnmbu((n % 10), sum);
	}
	else
		sum += ft_putchar(48 + n);
	return (sum);
}

int	ft_putnmbcx(unsigned int n, int sum, char *base)
{
	if (n >= 16)
	{
		sum = ft_putnmbcx((n / 16), sum, base);
		sum = ft_putnmbcx((n % 16), sum, base);
	}
	else
		sum += ft_putchar(base[n]);
	return (sum);
}

int	ft_putnmbx(unsigned int n, int sum, char *base)
{
	if (n >= 16)
	{
		sum = ft_putnmbx((n / 16), sum, base);
		sum = ft_putnmbx((n % 16), sum, base);
	}
	else
		sum += ft_putchar(base[n]);
	return (sum);
}

int	ft_putp(unsigned long long int n, int sum, char *base)
{
	if (n >= 16)
	{
		sum = ft_putp((n / 16), sum, base);
		sum = ft_putp((n % 16), sum, base);
	}
	else
		sum += ft_putchar(base[n]);
	return (sum);
}

int	ft_pad(unsigned long long int n, int sum, char *base)
{
	write(STDOUT_FILENO, "0x", 2);
	sum += 2;
	sum = ft_putp(n, sum, base);
	return (sum);
}
