/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:01:35 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/13 03:03:21 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s, char stop)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != stop)
		i++;
	return (i);
}

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen_gnl(dst, '\0');
	src_len = ft_strlen_gnl(src, '\0');
	if (!dst || !src)
		return (src_len + size);
	if (dest_len >= size)
		return (src_len + size);
	while (i < (size - dest_len) && src[i] != '\0' && (dest_len + i < size - 1))
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
	return (src_len + dest_len);
}

char	*ft_joindup(char *s1, char *s2, size_t size, int free_s)
{
	char	*str;
	size_t	len_s1;

	len_s1 = 1;
	if (s1)
		len_s1 += ft_strlen_gnl(s1, 0);
	if (len_s1 + size <= 1)
		return (NULL);
	str = malloc(sizeof(char) * (len_s1 + size));
	if (!str)
		return (NULL);
	*str = '\0';
	if (s1)
	{
		ft_strlcat_gnl(str, s1, len_s1 + size);
		if (free_s == 1 || free_s == 3)
			free(s1);
	}
	if (s2)
	{
		ft_strlcat_gnl(str, s2, len_s1 + size);
		if (free_s == 2 || free_s == 3)
			free(s2);
	}
	return (str);
}
