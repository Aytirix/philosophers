/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:25:25 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/13 03:36:12 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	checker(const char *str, va_list args, int fd)
{
	if (*str == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (*str == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (*str == 'p')
		return (ft_putaddress(va_arg(args, long long), fd));
	else if (*str == 'd' || *str == 'i')
		return (ft_putnbr_base_fd(va_arg(args, int), "0123456789", fd));
	else if (*str == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), "0123456789",
				fd));
	else if (*str == 'x')
		return (ft_putunbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", fd));
	else if (*str == 'X')
		return (ft_putunbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd));
	else if (*str == '%')
		return (ft_putstr_fd("%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
			count += checker(++str, args, STDOUT_FILENO);
		else
			count += ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (count);
}
