/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:28:14 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/24 14:28:14 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int s_free)
{
	char	*s;
	int		len;

	len = 1;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	s = ft_calloc(sizeof(char), len);
	if (s && s1)
	{
		ft_strlcpy(s, s1, len);
		if (s_free == 1 || s_free == 3)
			free((char *)s1);
	}
	if (s && s2)
	{
		ft_strlcat(s, s2, len);
		if (s_free == 2 || s_free == 3)
			free((char *)s2);
	}
	return (s);
}
