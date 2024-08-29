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

int	ft_putaddress(unsigned long long address, int fd)
{
	int	count;

	count = 0;
	if (!address)
		return (ft_putstr_fd("(nil)", fd));
	count += ft_putstr_fd("0x", 1);
	if (address == -1ULL)
		return (ft_putstr_fd("ffffffffffffffff", fd));
	count += ft_putunbr_base_fd(address, "0123456789abcdef", fd);
	return (count);
}
