/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:47:07 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/10 12:08:01 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// 	return (1);
// }

// static int	ft_putstring(char *astring, int sum)
// {
// 	int	x;

// 	x = -1;
// 	while (astring[++x] != 0)
// 		sum += ft_putchar(astring[x]);
// 	return (sum);
// }

// static int	ft_putnmb(int n, int sum)
// {
// 	if (n == -2147483648)
// 	{
// 		sum += ft_putchar('-');
// 		sum += ft_putchar('2');
// 		n = 147483648;
// 	}
// 	if (n < 0)
// 	{
// 		sum += ft_putchar('-');
// 		n *= -1;
// 	}
// 	if (n >= 10)
// 	{
// 		sum = ft_putnmb((n / 10), sum);
// 		sum = ft_putnmb((n % 10), sum);
// 	}
// 	else
// 		sum += ft_putchar(48 + n);
// 	return (sum);
// }

static int	ft_type(va_list args, const char *string, int sum, int x)
{
	if (string[x] == 'c')
		sum += ft_putchar(va_arg(args, int));
	else if (string[x] == 's')
		ft_printftypestring(args, NULL, sum);
	else if (string[x] == 'd' || string[x] == 'i')
		sum = ft_putnmb(va_arg(args, int), sum);
	else if (string[x] == 'u')
		sum = ft_putnmbu(va_arg(args, unsigned int), sum);
	else if (string[x] == '%')
		sum += ft_putchar('%');
	else if (string[x] == 'x')
		sum = ft_putnmbx(va_arg(args, unsigned int), sum, "0123456789abcdef");
	else if (string[x] == 'X')
		sum = ft_putnmbcx(va_arg(args, unsigned int), sum, "0123456789ABCDEF");
	else if (string[x] == 'p')
		sum = ft_pad(va_arg(args, unsigned long long), sum, "0123456789abcdef");
	else if (string[x] == 'b')
		sum += ft_printbits(8, va_arg(args, int));
	else if (string[x] == 'B')
		sum += ft_printbits(16, va_arg(args, int));
	else if (string[x] == 'i')
		sum += ft_printbits(32, va_arg(args, int));
	return (sum);
}

int	ft_printd(int flag, const char *string, ...)
{
	int		sum;
	va_list	args;
	int		x;

	va_start(args, string);
	x = -1;
	sum = 0;
	if (flag)
	{
		while (string[++x] != 0)
		{
			if (string[x] == '%')
				sum = ft_type(args, string, sum, ++x);
			else
				sum += ft_putchar(string[x]);
		}
	}
	va_end(args);
	return (sum);
}
