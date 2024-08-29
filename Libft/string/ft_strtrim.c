/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:16:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/24 15:16:54 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*dest;

	dest = NULL;
	if (s1)
	{
		while (*s1 && set && ft_strchr(set, (int)*s1))
			s1++;
		i = ft_strlen(s1);
		while (i > 0 && set && ft_strchr(set, (int)s1[i - 1]))
			i--;
		dest = ft_calloc(i + 1, sizeof(char));
		if (dest)
			ft_strlcpy(dest, s1, i + 1);
	}
	return (dest);
}
