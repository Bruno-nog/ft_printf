/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:45:41 by brunogue          #+#    #+#             */
/*   Updated: 2024/11/18 12:23:42 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putnbr_u(unsigned int n);
int		ft_putnbr_hex(unsigned long n, const char *base);
int	ft_putnbr(int n);
int		ft_printf(const char *format, ...);

#endif