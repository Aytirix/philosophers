/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:34:34 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/30 02:34:34 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_base_fd(long long nb, char *base, int fd)
{
	long long	baselen;
	int			count;

	count = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		count++;
		nb = nb * -1;
	}
	baselen = ft_strlen(base);
	if (nb >= baselen)
		count += ft_putnbr_base_fd(nb / baselen, base, fd);
	count += ft_putchar_fd(base[nb % baselen], fd);
	return (count);
}

int	ft_putunbr_base_fd(unsigned long long nb, char *base, int fd)
{
	unsigned long long	baselen;
	int					count;

	count = 0;
	baselen = ft_strlen(base);
	if (nb >= baselen)
		count += ft_putnbr_base_fd(nb / baselen, base, fd);
	count += ft_putchar_fd(base[nb % baselen], fd);
	return (count);
}
