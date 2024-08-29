/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:11:13 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/23 14:11:13 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	s = (void *)malloc(size * nmemb);
	if (!s)
		return (NULL);
	ft_bzero(s, (size * nmemb));
	return (s);
}
