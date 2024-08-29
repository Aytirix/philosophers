/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:19:30 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/25 15:19:30 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	solve(int n, char **str, int len)
{
	while (len-- > 0 && (*str)[len] != '-')
	{
		if (n < 0)
			(*str)[len] = -(n % 10) + '0';
		else
			(*str)[len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		nb;

	len = 0;
	nb = n;
	if (n < 0 || n == 0)
		len++;
	while (nb != 0)
	{
		nb /= 10 ;
		len++;
	}
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!(str))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	solve(n, &str, len);
	return (str);
}
