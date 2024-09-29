/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	s = (void *)malloc(size * nmemb);
	if (!s)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		((char *)s)[i++] = 0;
	return (s);
}

void	*update_death(t_tools *tools)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&tools->phils[0].m_stop);
	if (tools->phils[0].stop)
	{
		pthread_mutex_unlock(&tools->phils[0].m_stop);
		return (NULL);
	}
	pthread_mutex_unlock(&tools->phils[0].m_stop);
	while (++i < tools->nb_phil)
	{
		pthread_mutex_lock(&tools->phils[i].m_stop);
		tools->phils[i].stop = 1;
		pthread_mutex_unlock(&tools->phils[i].m_stop);
	}
	return (NULL);
}
