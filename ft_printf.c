/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:04:19 by brunogue          #+#    #+#             */
/*   Updated: 2024/11/18 14:39:24 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write (1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (0);
	}
	while (s[i])
	{
		write(1, &s[i++], 1);
	}
	return (i);
}

int ft_putnbr_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_u(n / 10);
	}
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putnbr_hex(unsigned long n, const char *base)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hex(n / 16, base);
	}
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_putnbr(int n)
{
	unsigned int	nb;
	int				count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
	}
	if (n < 0)
	{
		ft_putchar('-');
		nb = -n;
	}
	nb = (unsigned int)n;
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
	}
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;
	unsigned long	ptr;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				count += ft_putchar('%');
			else if (format[i] == 'c')
				count += ft_putchar(va_arg(args, int));
			else if (format[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (format[i] == 'd' || format[i] == 'i')
				ft_putnbr(va_arg(args, int));
			else if (format[i] == 'u')
				count += ft_putnbr_u(va_arg(args, unsigned int));
			else if (format[i] == 'p')
			{
				ptr = (unsigned long)va_arg(args, void *);
				count += ft_putstr("0x");
				count += ft_putnbr_hex(ptr, "0123456789abcdef");
			}
			else if (format[i] == 'x')
				count +=  ft_putnbr_hex(va_arg(args, unsigned int), "0123456789abcdef");
			else if (format[i] == 'X')
				count += ft_putnbr_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*
//cc -w ft_printf.c ft_printf.h ft_printf_utils.c ft_printf_utils2.c
#include <stdio.h>
#include <limits.h>
int	main(void)
{
	char ch = 'A';
	char *str = "string";
	int i = -42;
	int j = -42;
	unsigned int u = 42;
    int count;
    count = 0;
	//Test 1: c, s, d, i
	printf("Test1\n");
	count = ft_printf("%s  %c  %d  %i\n", str, ch, i, i);
	printf("ft_printf count = %d\n\n", count);
	count = printf("%s  %c  %d  %i\n", str, ch, i, i);
    printf("printf count = %d\n\n\n", count);
	//Test 2: p
	printf("Test2\n\n");
    count = ft_printf("p: %p\n\n", str);
	printf("ft_printf count = %d\n\n", count); 
	count = printf("p: %p\n\n", str);
	printf("printf count = %d\n\n\n", count);
	//Test 3: u
	printf("Test3\n");
    count = ft_printf("unsigned: %u\n", u);
	printf("ft_printf count = %d\n\n", count);
	count = printf("unsigned: %u\n", u);
	printf("printf count = %d\n\n\n", count);
	//Test 4: u but sending negative int
	printf("Test4\n");
    count = ft_printf("unsigned: %u\n", j);
	printf("ft_printf count = %d\n\n", count);
	count = printf("unsigned: %u\n", j);
	printf("printf count = %d\n\n\n", count);
	//Test 5: x
	printf("Test5\n");
	count = ft_printf("hex: %x\n", i);
	printf("ft_printf count = %d\n\n", count);
	ft_printf("hex: %x\n", i);
	printf("printf count = %d\n\n\n", count);
	//Test 6: X
	printf("Test6\n");
	count = ft_printf("hex: %X\n", i);
	printf("ft_printf count = %d\n\n", count);
	ft_printf("hex: %X\n", i);
	printf("printf count = %d\n\n\n", count);
	//Test 7: %%
	printf("Test7\n");
	count = ft_printf("percentage %%\n");
	printf("ft_printf count = %d\n\n", count);
	count = printf("percentage %%\n");
	printf("printf count = %d\n\n\n", count);
	//Test 8: %j - an invalid argument
	printf("Test8\n");
    count = ft_printf("f%jk\n", i);
	printf("ft_printf count = %d\n\n", count);
	count = printf("f%jk\n", i);
	printf("printf count = %d\n\n\n", count);
	//Test 9: s (null)
	printf("Test9\n");
	count = ft_printf(" NULL %s NULL\n", NULL);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" NULL %s NULL\n", NULL);
	printf("printf count = %d\n\n\n", count);
	//Test 10: s (sending 0)
	printf("Test10\n");
	count = ft_printf(" NULL %s NULL\n", 0);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" NULL %s NULL\n", 0);
	printf("printf count = %d\n\n\n", count);
	//Test 11: p (long address)
	//(long) LONG_MAX: 2147483647;  LONG_MIN: -2147483648;
	printf("Test11\n");
	count = ft_printf(" %p %p \n", LONG_MIN, LONG_MAX);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" %p %p \n", LONG_MIN, LONG_MAX);
	printf("printf count = %d\n\n\n", count);
	//Test 12: p (unsigned long address)
	printf("Test12\n");
	count = ft_printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
	printf("printf count = %d\n\n\n", count);
	//Test 13: p (nil) (sending 0)
	printf("Test13\n");
	count = ft_printf(" %p %p \n", 0, 0);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" %p %p \n", 0, 0);
	printf("printf count = %d\n\n\n", count);
	//Test 14: hex (sending 0)
	printf("Test14\n");
	count = ft_printf(" %x %x \n", 0, 0);
	printf("ft_printf count = %d\n\n", count);
	count = printf(" %x %x \n", 0, 0);
	printf("printf count = %d\n\n\n", count);
	//Test 15: with no arguments
	printf("Test15\n");
	count = ft_printf("Hi %d Hai\n");
	printf("ft_printf count = %d\n\n", count);
	count = printf("Hi %d Hai\n");
	printf("printf count = %d\n\n\n", count);
	//Test 16
	//undefined behavior, it can lead to seg fault or crash
	printf("Test16\n");
	count = printf(NULL);
	printf("printf count = %d\n\n", count);
	count = ft_printf(NULL);
	printf("ft_printf count = %d\n\n\n", count);
	//string/Test 17
	printf("Test17\n");
	count = printf("%s\n", "");
	printf("printf count = %d\n", count);
	count = ft_printf("%s\n", "");
	printf("ft_printf count = %d\n\n", count);
}*/