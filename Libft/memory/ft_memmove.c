/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:32:39 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/20 01:38:12 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*source;

	dst = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (dst < source)
	{
		while (n--)
			*dst++ = *source++;
	}
	else
	{
		dst += n;
		source += n;
		while (n--)
			*--dst = *--source;
	}
	return (dest);
}
