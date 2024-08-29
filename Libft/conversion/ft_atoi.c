/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/04/23 11:17:39 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/23 11:17:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	i = 0;
	sign = 1;
	while (((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
		result = result * 10 + nptr[i++] - '0';
	if (((i > 10 || result > INT_MAX) && sign == 1) || ((i > 10
				|| result > ((INT_MIN) * -1LL)) && sign == -1))
		return (0);
	return (sign * result);
}
